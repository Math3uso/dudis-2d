#include "dudis2d/graphics/renderable.h"
#include "dudis2d/graphics/shape.h"

#pragma once

namespace dudis {

enum class FillMode { Outile, Filled };

class DDRectangle : public Renderable {
protected:
  Rectangle rect;
  dudis::FillMode fill;

public:
  DDRectangle(SizeI size, Vec2 pos = {0, 0},
              dudis::FillMode fill = dudis::FillMode::Filled);
  void render() override;
  void update() override {};

  static std::shared_ptr<DDRectangle> create(SizeI size, Vec2 pos = {0, 0}) {
    return std::make_shared<DDRectangle>(size, pos);
  }
};
} // namespace dudis