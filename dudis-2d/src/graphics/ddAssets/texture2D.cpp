#include "dudis2d/graphics/ddAssets/texture2D.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/graphics/ddrlUtils/ddrlUtils.h"

using namespace std;
using namespace dudis;
using namespace res;

DDTexture res::Texture2DManager::_create(const char *path, DDTexture &ddTex,
                                         uint32_t *id, DDTextureFilter filter)
{

  auto key = string(path);
  auto it = _rlTextures.find(key);

  if (it != _rlTextures.end())
  {
    puts("enviado do cache");
    return DDTexture(it->second);
  }

  Image img = LoadImage(path);
  TextureFormat fmt = ddrlUtils::mapRaylibFormat((PixelFormat)img.format);

  auto rlTex = LoadTextureFromImage(img);

  SetTextureFilter(rlTex, ddrlUtils::mapToRLFilter(filter));

  printf("img.format=%d  rlTex.format=%d\n", img.format, rlTex.format);

  UnloadImage(img);

  if (id)
  {
    *id = rlTex.id;
  }

  ddTex.width = rlTex.width;
  ddTex.height = rlTex.height;
  ddTex.id = rlTex.id;
  ddTex.formate = fmt;

  ddTex.mipmaps = 1;

  _rlTextures.emplace(key, rlTex);

  ddTex._rlTex = &_rlTextures[key];

  return ddTex;
}

DDTexture res::Texture2DManager::create(const char *path, DDTextureFilter filter)
{
  DDTexture ddTex = DDTexture(0, TextureFormat::RGBA8);

  ddTex.mipmaps = 1;

  return this->_create(path, ddTex, nullptr, filter);
}

void res::Texture2DManager::unload(const DDTexture &tex)
{
  if (tex.id != 0)
  {
    rlUnloadTexture(tex.id);
    Log::Success("Textura removida");
  }
}

void res::Texture2DManager::unloadAll()
{
  for (auto &i : _rlTextures)
  {
    this->unload(i.second);
  }
}