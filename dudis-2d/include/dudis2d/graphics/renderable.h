#pragma once

#include "dudis2d/core/entity/entity.h"
#include "dudis2d/graphics/ddAssets/texture2D.h"
#include "dudis2d/scenes/sceneProperty/sceneProperty.h"
#include "dudis2d/core/math/rect.h"
#include "dudis2d/graphics/color.h"

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
    SceneProperty sceneProps;
    std::string filePath;
    DDRect _rectSrc;
    DDRect _rectDest;
    bool _tex = false;
    rl::RlTexture *_rlTex;

  public:
    const char *name;

    Renderable() {};
    virtual ~Renderable() { puts("renderable deletado [Renderable]"); };
    void render() override = 0;
    void update() override {};

    dudis::TypeShape Type() const { return type; }
    virtual void buildRenderCommands(RenderQueue *queue) override;

    const Color &getColor() const { return color; }
    const res::DDTexture getTexture() const;
    SceneProperty &getSceneProps() { return sceneProps; }

    void setColor(const Color &nColor) { color = nColor; }
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