#include "dudis2d/graphics/ddAssets/ddTexture.h"
#include "dudis2d/graphics/ddrlUtils/ddrlUtils.h"

using namespace dudis;
using namespace res;

DDTexture::DDTexture(rl::RlTexture &rltex) {
  id = rltex.id;
  formate = ddrlUtils::mapRaylibFormat((PixelFormat)rltex.format);
  width = rltex.width;
  height = rltex.height;
  mipmaps = rltex.mipmaps;
  this->_rlTex = &rltex;
  puts("criado apartir de um rlTexture");
}