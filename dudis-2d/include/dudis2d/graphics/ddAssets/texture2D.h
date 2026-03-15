#pragma once

#include "dudis2d/graphics/ddAssets/ddTexture.h"
#include "rlgl.h"
#include <string>
#include <unordered_map>
#include "dudis2d/graphics/ddAssets/ddTextureFilter.h"

namespace dudis
{

  class Sprite;

  namespace res
  {

    class Texture2DManager;

    class Texture2DManager
    {
    private:
      std::unordered_map<std::string, rl::RlTexture> _rlTextures;
      // std::unordered_map<std::string, DDTexture> _ddTextures;

      // recursos alocanos na scene, ddTexObject é um alias de std::unordered_map<std::string, rl::RlTextur
      // std::unordered_map<std::string, ddTexObject> _sceneRes;

      DDTexture _create(const char *path, DDTexture &ddTex, uint32_t *id, DDTextureFilter filter);
      friend DDTexture;

    public:
      Texture2DManager() = default;
      DDTexture create(const char *path, DDTextureFilter filter = TextureFilter::Nearest);
      DDTexture create(const char *path);

      void unload(const DDTexture &tex);
      void unloadAll();
      //  DDTexture _rlTex2DFromDDTex(const rl::RlTexture &rltex);
    };
  } // namespace res
} // namespace dudis