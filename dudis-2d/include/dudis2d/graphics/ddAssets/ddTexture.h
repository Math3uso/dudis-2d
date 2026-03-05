#pragma once

#include "dudis2d/core/utils/types.h"
#include "dudis2d/graphics/ddAssets/ddTextureTypeUtils.h"
#include <cstdint>

namespace dudis
{

  class Sprite;

  namespace res
  {

    class Texture2DManager;

    class DDTexture
    {
    public:
      DDTexture(uint32_t id, TextureFormat nFormate = TextureFormat::RGB8)
          : id(id), formate(nFormate) {};
      DDTexture() = default;
      uint32_t id;
      uint32_t width;
      uint32_t height;
      TextureFormat formate;
      uint8_t mipmaps;
      friend res::Texture2DManager;
      friend Sprite;

    private:
      bool _cache = false;
      int _refCount = 0;
      rl::RlTexture *_rlTex = nullptr;
      DDTexture(rl::RlTexture &rltex);
    };
  } // namespace res
} // namespace dudis