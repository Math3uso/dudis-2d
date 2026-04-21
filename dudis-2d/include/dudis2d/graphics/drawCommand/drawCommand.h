#pragma once

#include "dudis2d/graphics/ddAssets/texture2D.h"
#include "dudis2d/graphics/commandState.h"
#include "dudis2d/graphics/blendType.h"
#include "dudis2d/core/math/vec2.h"
#include "dudis2d/core/math/rect.h"
#include "dudis2d/graphics/color.h"
#include "dudis2d/core/utils/sizeF.h"

#ifdef DD_DEBUG
#include "dudis2d/core/debug/dd-debug.h"
#endif

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
    uint32_t texId = 0;
    DDRect src;
    Color color = {255, 255, 255, 255};
    DDPrimitiveType type;
    DDBatchType batch{0};
    int z;
    BlendType blendType;

    DDRect scissorRect;

    CommandState cmdState;

#ifdef DD_DEBUG
    friend std::ostream &operator<<(std::ostream &os, const DrawCommand &c)
    {
      os << "DrawCommand { "
         << "pos: [" << c.pos.x << ", " << c.pos.y << "], "
         << "scale: [" << c.scale.x << ", " << c.scale.y << "], "
         << "size: [" << c.size.w << ", " << c.size.h << "], "
         << "rotation: " << c.rotation << ", "
         << "texId: " << c.texId << ", "
         << "z: " << c.z << ", "
         << "batch: " << (int)c.batch << ", "
         << "cmdState: " << DD_Debug_CmdStateToString(c.cmdState) << " } "
         << "bType: " << DD_Debug_BlendModeToStr(c.blendType);
      return os;
    }
#endif
  };

} // namespace dudis