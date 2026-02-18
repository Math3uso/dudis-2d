#pragma once

#include "dudis2d/graphics/drawCommand/drawCommand.h"

namespace dudis
{

  class DDRender
  {
  public:
    DDRender() = default;
    void init() {};
    void draw(const std::vector<DrawCommand> &cmd);
    static std::shared_ptr<DDRender> create()
    {
      return std::make_shared<DDRender>();
    }
  };
} // namespace dudis