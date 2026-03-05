#include "dudis2d/graphics/sprites/sprite/sprite.h"

#include <cmath>

#include "dudis2d/core/log/log.h"
#include "dudis2d/graphics/drawCommand/drawCommand.h"

using namespace dudis;
using namespace std;

Sprite::Sprite(const char *texturPath, Size size)
{
  pos = {0, 0};
  _rectSrc = {0, 0, 0, 0};
  _tex = true;

  this->filePath = std::string(texturPath);

  this->size = size;

  this->type = TypeShape::Rectangle;
}
Sprite::~Sprite()
{
  Log::Alert("[INFO] liberando recursos [Sprite]");

  // res::Texture2D::unload(_rlTex->id);
  Log::Info("[INFO] recursos de sprite liberado [Sprite]");
}

void Sprite::start()
{
  if (!_createTexture)
  {
    auto path = filePath.c_str();
    // _ddTex = res::Texture2D::create(path, res::TextureLoadMode::Uncached);
    auto _ddTex = res::Texture2D::create(path);
    _rlTex = _ddTex._rlTex;
    return;
  }
  return;
}

void Sprite::render() {}

shared_ptr<Sprite> Sprite::create(const char *texturPath, Size size)
{
  auto sprite = make_shared<Sprite>(texturPath, size);
  sprite->_createTexture = false;
  sprite->start();
  return sprite;
}

DDRef Sprite::create(const char *path, Size size, res::DDTexture tex)
{
  auto sprite = make_shared<Sprite>(path, size);
  sprite->_createTexture = true;
  sprite->_rlTex = tex._rlTex;
  sprite->start();
  return sprite;
}