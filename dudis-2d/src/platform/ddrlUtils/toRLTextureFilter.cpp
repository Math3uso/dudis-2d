#include "dudis2d/platform/ddrlUtils/toRLTextureFilter.h"
#include "raylib.h"

namespace dudis
{
    namespace ddrlUtils
    {
        unsigned int toRLFilter(res::DDTextureFilter filter)
        {
            switch (filter)
            {
            case res::DDTextureFilter::Nearest:
                return TEXTURE_FILTER_POINT;

            case res::DDTextureFilter::Smooth:
                return TEXTURE_FILTER_BILINEAR;
            }

            return TEXTURE_FILTER_POINT;
        }
    }
}
