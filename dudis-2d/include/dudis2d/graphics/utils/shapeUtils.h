#pragma once
#include "dudis2d/graphics/renderable.h"
#include <memory>

// class Renderable;

namespace dudis {
class ShapeUtils {
public:
  static dudis::Vec2 Center(std::weak_ptr<Renderable> shape);
  static dudis::Vec2 FullTopLeft(std::weak_ptr<Renderable> shape);
  // static dudis::Vec2 FullTopRight(std::weak_ptr<Renderable> shape) {};
  // static dudis::Vec2 FullBottomRight(std::weak_ptr<Renderable> shape) {};
  // static dudis::Vec2 FullBottomLeft(std::weak_ptr<Renderable> shape) {};
};
} // namespace dudis
