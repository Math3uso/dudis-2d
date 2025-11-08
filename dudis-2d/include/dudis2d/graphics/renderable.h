#pragma once

#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/utils/types.h"
#include "dudis2d/scenes/sceneProperty/sceneProperty.h"

namespace dudis {

enum class TypeShape { Triangle, Rectangle, Circle };

class Renderable : public Entity {
protected:
  Vec2 origin = {0, 0};
  dudis::TypeShape type;
  Color color = WHITE;
  bool flippedX = false;
  SceneProperty sceneProps;
  std::string filePath;

public:
  int zIndex = -1;
  bool drawOrigin = false;
  const char *name;

  Renderable() {};
  virtual ~Renderable() { puts("renderable deletado [Renderable]"); };
  virtual void render() = 0;
  void update() override {};
  virtual void setFlippedX(bool flip) { flippedX = flip; };

  // const std::string &getFilePath() const {
  //   return filePath;
  // }

  Vec2 getOrigin() const { return origin; }
  Color getColor() const { return color; }
  dudis::TypeShape Type() const { return type; }

  SceneProperty &getSceneProps() { return sceneProps; }

  void rotate(float nAngle) { angle = nAngle; }
  void setOrigin(Vec2 nOrigin) { origin = nOrigin; }
  void setColor(Color nColor) { color = nColor; }
  void setOpacity(float opacity) {
    color = {color.r, color.g, color.b, (unsigned char)opacity};
  }
};
} // namespace dudis