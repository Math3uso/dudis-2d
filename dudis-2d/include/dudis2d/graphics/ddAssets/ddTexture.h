#pragma once

#include "dudis2d/graphics/ddAssets/ddTextureTypeUtils.h"
#include "dudis2d/graphics/ddAssets/ddTextureFilter.h"
#include <cstdint>
#include "dudis2d/core/utils/types.h"
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
      uint32_t id = 0;
      uint32_t width = 0;
      uint32_t height = 0;
      TextureFormat formate = TextureFormat::RGB8;
      uint8_t mipmaps = 1;
      void setFilter(res::TextureFilter filter);
      void setWrap(TextureWrap wrap);

      friend res::Texture2DManager;
      friend Sprite;

    private:
      bool _cache = false;
      int _refCount = 0;
      rl::RlTexture *_rlTex = nullptr;
      TextureFilter _filter = TextureFilter::Nearest;
      TextureWrap _wrap = TextureWrap::Repeat;

      DDTexture(rl::RlTexture &rltex);
    };
  } // namespace res
} // namespace dudis
