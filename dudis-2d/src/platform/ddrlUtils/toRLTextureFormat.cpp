#include "dudis2d/platform/ddrlUtils/toRLTextureFormat.h"
#include "raylib.h"

namespace dudis
{
    namespace ddrlUtils
    {
        unsigned int toRLTextureFormat(res::TextureFormat ddTexFormat)
        {
            switch (ddTexFormat)
            {
            case res::TextureFormat::RGBA8:
                return PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
            case res::TextureFormat::RGB8:
                return PIXELFORMAT_UNCOMPRESSED_R8G8B8;
            case res::TextureFormat::R8:
                return PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
            case res::TextureFormat::DXT1_RGB:
                return PIXELFORMAT_COMPRESSED_DXT1_RGB;
            default:
                return PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
            }
        }
    }
}
