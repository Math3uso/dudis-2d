#include "dudis2d/graphics/utils/shapeUtils.h"
#include "dudis2d/core/log/log.h"
// #include "graphics/renderable.h"

using namespace dudis;

dudis::Vec2 ShapeUtils::Center(std::weak_ptr<Renderable> shape)
{
  if (auto shapeRef = shape.lock())
  {
    const auto size = shapeRef->getSize();

    switch (shapeRef->Type())
    {
    case dudis::TypeShape::Rectangle:
      Vec2 center = {size.w / 2.f, size.h / 2.f};
      return center;
      break;
    }
  }
  dudis::Log::Error("pointer in not found");
  return Vec2{0, 0};
}