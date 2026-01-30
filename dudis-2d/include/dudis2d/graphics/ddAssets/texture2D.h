#pragma once

#include "dudis2d/graphics/ddAssets/ddTexture.h"
#include "rlgl.h"
#include <string>
#include <unordered_map>

namespace dudis {

class Sprite;

namespace res {

class Texture2D;

class Texture2D {
private:
  static std::unordered_map<std::string, rl::RlTexture> _rlTextures;
  static DDTexture _create(const char *path, DDTexture &ddTex, uint32_t *id);
  friend DDTexture;

public:
  // static DDTexture create(const char *path,
  //                         TextureLoadMode mode = TextureLoadMode::Uncached);

  static DDTexture create(const char *path);

  // static DDTexture create(const TextureInfo &info);
  static void unload(const DDTexture &tex);
  static DDTexture _rlTex2DFromDDTex(const rl::RlTexture &rltex);
};
} // namespace res
} // namespace dudis