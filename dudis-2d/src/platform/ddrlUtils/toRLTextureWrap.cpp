#include "dudis2d/platform/ddrlUtils/toRLTextureWrap.h"
#include "raylib.h"

namespace dudis
{
    namespace ddrlUtils
    {
        int toRLTextureWrap(res::TextureWrap wrap)
        {
            switch (wrap)
            {
            case res::TextureWrap::Repeat:
                return TEXTURE_WRAP_REPEAT;

            case res::TextureWrap::Clamp:
                return TEXTURE_WRAP_CLAMP;

            case res::TextureWrap::MirrorRepeat:
                return TEXTURE_WRAP_MIRROR_REPEAT;

            case res::TextureWrap::MirrorClamp:
                return TEXTURE_WRAP_MIRROR_CLAMP;
            }

            return TEXTURE_WRAP_REPEAT;
        }
    }
}
