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
    // Vec2 origin = {0, 0};
    dudis::TypeShape type;
    Color color = Color::White();
    bool flippedX = false;
    SceneProperty sceneProps;
    std::string filePath;
    DDRect _rectSrc;
    DDRect _rectDest;
    bool _tex = false;
    rl::RlTexture *_rlTex;
    res::DDTexture _ddTex;

  public:
    int zIndex = -1;
    bool drawOrigin = false;
    const char *name;

    Renderable() {};
    virtual ~Renderable() { puts("renderable deletado [Renderable]"); };
    void render() override = 0;
    void update() override {};

    virtual void buildRenderCommands(RenderQueue *queue) override;

    // const std::string &getFilePath() const {
    //   return filePath;
    // }

    // Vec2 getOrigin() const { return origin; }
    const Color &getColor() const { return color; }
    dudis::TypeShape Type() const { return type; }

    SceneProperty &getSceneProps() { return sceneProps; }

    // void rotate(float nAngle) { angle = nAngle; }
    //  void setOrigin(Vec2 nOrigin) { origin = nOrigin; }
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