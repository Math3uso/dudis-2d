#pragma once

#include "dudis2d/graphics/renderable.h"
#include <memory>

namespace dudis {
class Sprite : public Renderable {

protected:
  Texture2D texture;
  // Color color = WHITE;
  Rectangle rect;

public:
  Sprite(const char *texturPath, SizeI size);
  ~Sprite() {
    if (texture.id != 0) {
      UnloadTexture(texture);
      puts("recursos de sprite liberado [Sprite]");
    }
  }

  void setCrop(Rectangle src) { rect = src; }

  static std::shared_ptr<Sprite> create(const char *texturPath, SizeI size);

  void render() override;

  Texture2D &getTextureRef() { return texture; }
};
} // namespace dudis