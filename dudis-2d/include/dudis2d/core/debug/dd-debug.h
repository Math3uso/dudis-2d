#pragma once

namespace dudis
{

#ifdef DD_DEBUG

#include "dudis2d/graphics/commandState.h"
#include "dudis2d/graphics/blendType.h"

  inline const char *DD_Debug_CmdStateToString(CommandState b)
  {
    switch (b)
    {
    case CommandState::Draw:
      return "Draw";
    case CommandState::PushScissor:
      return "PushScissor";
    case CommandState::EndScissor:
      return "EndScissor";
    default:
      return "Unknow";
    }
  }

  inline const char *DD_Debug_BlendModeToStr(BlendType type)
  {
    switch (type)
    {
    case BlendType::AlphaComposite:
      return "AlphaComposite";
    case BlendType::LightAdd:
      return "LightAdd";
    case BlendType::ColorMultiply:
      return "ColorMultiply";
    case BlendType::ColorAdd:
      return "ColorAdd";
    case BlendType::ColorSubtract:
      return "ColorSubtract";
    case BlendType::PremultipliedAlpha:
      return "PremultipliedAlpha";
    default:
      return "Unknow";
    }
  }
#endif

} // namespace dudis