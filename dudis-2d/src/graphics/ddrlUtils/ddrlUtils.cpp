#include "dudis2d/graphics/ddrlUtils/ddrlUtils.h"
#include "raylib.h"

namespace dudis
{
  namespace ddrlUtils
  {

    res::TextureFormat mapRaylibFormat(unsigned int fmt)
    {
      switch (fmt)
      {
      case PIXELFORMAT_UNCOMPRESSED_R8G8B8A8:
        return res::TextureFormat::RGBA8;
      case PIXELFORMAT_UNCOMPRESSED_R8G8B8:
        return res::TextureFormat::RGB8;
      case PIXELFORMAT_UNCOMPRESSED_GRAYSCALE:
        return res::TextureFormat::R8;
      case PIXELFORMAT_COMPRESSED_DXT1_RGB:
        return res::TextureFormat::DXT1_RGB;
      default:
        return res::TextureFormat::RGBA8;
      }
    }

    unsigned int mapToRaylibFormat(res::TextureFormat fmt)
    {
      switch (fmt)
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

    unsigned int mapToRLFilter(res::DDTextureFilter filter)
    {
      switch (filter)
      {
      case res::TextureFilter::Smooth:
        return TEXTURE_FILTER_BILINEAR;
      case res::TextureFilter::Nearest:
        return TEXTURE_FILTER_POINT;
      default:
        return TEXTURE_FILTER_POINT;
      }
    }

  } // namespace ddrlUtils
} // namespace dudis