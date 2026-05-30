#include "dudis2d/graphics/renderable.h"
#include "dudis2d/core/math/rect.h"

#pragma once

namespace dudis
{

  enum class FillMode
  {
    Outile,
    Filled
  };

  class DDRectangle : public Renderable
  {
  protected:
    DDRect rect;
    dudis::FillMode fill;

  public:
    DDRectangle(SizeF size, Vec2 pos = {0, 0}, dudis::FillMode fill = dudis::FillMode::Filled);
    void render() override {};
    void update() override {};

    static std::shared_ptr<DDRectangle> create(SizeF size, Vec2 pos = {0, 0}, dudis::FillMode fill = dudis::FillMode::Filled)
    {
      return std::make_shared<DDRectangle>(size, pos, fill);
    }
  };
} // namespace dudis
