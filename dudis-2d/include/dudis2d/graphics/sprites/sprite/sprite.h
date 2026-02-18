#pragma once

#include "dudis2d/core/log/log.h"
#include "dudis2d/graphics/renderable.h"
#include <memory>

namespace dudis
{

  class Sprite;
  using DDRef = std::shared_ptr<Sprite>;

  class Sprite : public Renderable
  {

  protected:
    // Color color = WHITE;
    // Rectangle rect;
    DDRect rect;
    bool _createTexture = false;

  public:
    Sprite(const char *texturPath, Size size);
    ~Sprite();

    void start() override;

    // void setCrop(Rectangle src) { rect = src; }
    void setCrop(DDRect src) { _rectSrc = src; }

    static std::shared_ptr<Sprite> create(const char *texturPath, Size size);
    static DDRef create(const char *path, Size size, res::DDTexture tex);

    void render() override;

    // Texture2D &getTextureRef() { return texture; }
  };
} // namespace dudis