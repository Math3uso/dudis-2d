#include "dudis2d/core/ddrlUtils/toRLBlendType.h"
#include "raylib.h"

namespace dudis
{
    namespace ddrlUtils
    {
        int toRLBlendType(BlendType type)
        {
            switch (type)
            {
            case BlendType::AlphaComposite:
                return BLEND_ALPHA;

            case BlendType::LightAdd:
                return BLEND_ADDITIVE;

            case BlendType::ColorMultiply:
                return BLEND_MULTIPLIED;

            case BlendType::ColorAdd:
                return BLEND_ADD_COLORS;

            case BlendType::ColorSubtract:
                return BLEND_SUBTRACT_COLORS;

            case BlendType::PremultipliedAlpha:
                return BLEND_ALPHA_PREMULTIPLY;

            case BlendType::UserDefined:
                return BLEND_CUSTOM;

            case BlendType::UserDefinedSeparate:
                return BLEND_CUSTOM_SEPARATE;
            }

            return BLEND_ALPHA;
        }
    }
}
