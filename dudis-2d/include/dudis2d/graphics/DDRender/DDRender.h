#pragma once

#include "dudis2d/graphics/drawCommand/drawCommand.h"
#include "dudis2d/graphics/blendType.h"

namespace dudis
{

  class RenderQueue;

  class DDRender
  {
  private:
    static int _drawCalls;

  public:
    DDRender() = default;
    void init() {};
    void draw(const std::vector<DrawCommand> &cmd, RenderQueue *queue);
    static std::shared_ptr<DDRender> create()
    {
      return std::make_shared<DDRender>();
    }

    static void defineRLDrawCalls();
    static int getDrawCalls() { return _drawCalls; }

    static void setBlendType(BlendType type);
  };
} // namespace dudis