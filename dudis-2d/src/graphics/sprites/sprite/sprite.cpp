#include "dudis2d/graphics/sprites/sprite/sprite.h"
#include "dudis2d/core/log/log.h"
#include <cmath>

using namespace dudis;
using namespace std;

Sprite::Sprite(const char *texturPath, SizeI size) {
  texture = LoadTexture(texturPath);
  pos = {0, 0};

  this->filePath = std::string(texturPath);

  this->size = size;

  this->type = TypeShape::Rectangle;

  if (texture.id == 0) {
    Log::Error("Erro ao carregar textura");
    return;
  }

  this->rect = {0, 0, (float)texture.width, (float)texture.height};
}

void Sprite::render() {

  Rectangle dest = {pos.x, pos.y, (float)size.w, (float)size.h};
  Rectangle sourceRect = rect;

  if (flippedX) {
    sourceRect.width = -rect.width;
  }

  DrawTexturePro(texture, sourceRect, dest, origin, angle, color);

  // DrawTexturePro(texture, rect, dest, origin, angle, color);
}

shared_ptr<Sprite> Sprite::create(const char *texturPath, SizeI size) {
  auto sprite = make_shared<Sprite>(texturPath, size);
  return sprite;
}