#include "dudis2d/graphics/ddrlUtils/ddrlUtils.h"

namespace dudis {
namespace ddrlUtils {

res::TextureFormat mapRaylibFormat(PixelFormat fmt) {
  switch (fmt) {
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

PixelFormat mapToRaylibFormat(res::TextureFormat fmt) {
  switch (fmt) {
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

} // namespace ddrlUtils
} // namespace dudis