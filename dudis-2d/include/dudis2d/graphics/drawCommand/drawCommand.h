#pragma once

#include "dudis2d/core/utils/types.h"

namespace dudis {

class DrawCommand {
public:
  Vec2 pos;
  Vec2 scale;
  Size size;
  float rotation;
  Vec2 origin;
  uint32_t tex;
  DDRect src;
  Color color;
  DDPrimitiveType type;
  int z;
};

} // namespace dudis