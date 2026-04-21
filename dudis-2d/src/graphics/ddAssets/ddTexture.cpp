#include <iostream>
#include "dudis2d/graphics/ddAssets/ddTexture.h"
#include "dudis2d/graphics/ddrlUtils/ddrlUtils.h"
#include "dudis2d/platform/ddrlUtils/toRLTextureWrap.h"
#include "dudis2d/platform/ddrlUtils/toRLTextureFilter.h"
#include "dudis2d/platform/ddrlUtils/toRLTextureFormat.h"
// #include "dudis2d/core/utils/types.h"
#include "dudis2d/core/utils/types.h"

using namespace dudis;
using namespace res;

DDTexture::DDTexture(rl::RlTexture &rltex)
{

  id = rltex.id;
  formate = ddrlUtils::mapRaylibFormat((PixelFormat)rltex.format);
  width = rltex.width;
  height = rltex.height;
  mipmaps = rltex.mipmaps;
  this->_rlTex = &rltex;
  puts("criado apartir de um rlTexture");
}

void DDTexture::setWrap(TextureWrap wrap)
{
  if (_wrap != wrap && _rlTex)
  {
    _wrap = wrap;
    SetTextureWrap(*_rlTex, (unsigned int)ddrlUtils::toRLTextureWrap(wrap));
    return;
  }
  return;
}

void DDTexture::setFilter(res::TextureFilter filter)
{
  if (_filter != filter && _rlTex)
  {
    _filter = filter;
    SetTextureFilter(*_rlTex, ddrlUtils::mapToRLFilter(_filter));
    return;
  }
  return;
}
