#pragma once

#include "dudis2d/core/entity/entity.h"
#include "dudis2d/graphics/ddAssets/texture2D.h"
#include "dudis2d/scenes/sceneProperty/sceneProperty.h"
#include "dudis2d/core/math/rect.h"
#include "dudis2d/graphics/color.h"
#include "dudis2d/graphics/blendType.h"

namespace dudis
{

  enum class TypeShape
  {
    Triangle,
    Rectangle,
    Circle
  };

  class Renderable : public Entity
  {
  protected:
    dudis::TypeShape type;
    Color color = Color::White();
    bool flippedX = false;
    bool _hasScissor = false;
    bool _tex = false;
    SceneProperty sceneProps;
    std::string filePath;
    DDRect _rectSrc;
    DDRect _rectDest;
    rl::RlTexture *_rlTex = nullptr;
    BlendType _blendType = BlendType::AlphaComposite;

  public:
    const char *name;

    Renderable() { _isRenderable = true; };
    virtual ~Renderable() { puts("renderable deletado [Renderable]"); };
    void render() override {};
    void update() override {};

    dudis::TypeShape Type() const { return type; }
    virtual void buildRenderCommands(RenderQueue *queue) override;

    const Color &getColor() const { return color; }
    const res::DDTexture getTexture() const;
    SceneProperty &getSceneProps() { return sceneProps; }
    bool hasTexture() { return _tex; }
    bool hasScissor() { return _hasScissor; }
    const DDRect &getRectSrc() const { return _rectSrc; }
    BlendType getBlendMode() { return _blendType; }

    rl::RlTexture *_getTextureData() { return _rlTex; }

    void setColor(const Color &nColor) { color = nColor; }
    void setHiddenOverfflow(bool isHidden) { _hasScissor = isHidden; }
    void setBlendMode(BlendType type) { _blendType = type; }

    virtual void setFlippedX(bool flip)
    {
      this->setDirty();
      flippedX = flip;
    };
    void setOpacity(float opacity)
    {
      this->setDirty();
      color = {color.r, color.g, color.b, (unsigned char)opacity};
    }
  };
} // namespace dudis