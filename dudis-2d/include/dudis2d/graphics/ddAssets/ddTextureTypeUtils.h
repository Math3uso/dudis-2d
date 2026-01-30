#pragma once

namespace dudis {
namespace res {

enum class TextureFormat { RGBA8, RGB8, R8, DXT1_RGB };

enum class TextureLoadMode { Cached, Uncached };

struct TextureInfo {
  const char *path;
  bool cache;
  bool mipmaps;
};

} // namespace res
} // namespace dudis