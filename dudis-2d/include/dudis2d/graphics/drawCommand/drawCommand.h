#pragma once

#include "dudis2d/core/utils/types.h"
#include "dudis2d/graphics/ddAssets/texture2D.h"

namespace dudis
{

  class DrawCommand
  {
  public:
    Vec2 pos;
    Vec2 scale;
    SizeF size;
    float rotation;
    Vec2 origin;
    bool _tex;
    rl::RlTexture rlTex;
    uint32_t texId;
    DDRect src;
    Color color;
    DDPrimitiveType type;
    DDBatchType batch;
    int z;
  };

} // namespace dudis