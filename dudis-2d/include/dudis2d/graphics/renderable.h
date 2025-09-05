#pragma once

#include "dudis2d/core/utils/types.h"
#include "dudis2d/scenes/sceneProperty/sceneProperty.h"

namespace dudis {

enum class TypeShape { Triangle, Rectangle, Circle };

class Renderable {
protected:
  dudis::SizeI size;
  dudis::Vec2 pos;
  Vec2 origin = {0, 0};
  float angle = 0.0f; // in radians
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
  virtual void update() {};
  virtual void setPos(dudis::Vec2 nPos) { pos = nPos; }
  virtual void setSize(dudis::SizeI nSize) { size = nSize; }
  virtual void setFlippedX(bool flip) { flippedX = flip; };
  virtual void translate(dudis::Vec2 nPos) {
    pos.x += nPos.x;
    pos.y += nPos.y;
  }

  // const std::string &getFilePath() const {
  //   return filePath;
  // }

  float getAngle() const { return angle; }
  Vec2 getOrigin() const { return origin; }
  dudis::Vec2 getPos() const { return pos; }
  dudis::SizeI getSize() const { return size; }
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