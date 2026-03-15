#pragma once

#include "dudis2d/core/log/log.h"
#include "dudis2d/graphics/renderable.h"
#include <memory>
#include "dudis2d/graphics/ddAssets/resTex2dUtils.h"

namespace dudis
{

  class Sprite;
  using DDRef = std::shared_ptr<Sprite>;

  class Sprite : public Renderable
  {

  protected:
    bool _createTexture = false;
    res::DDTextureFilter _filter;

  public:
    Sprite(const char *texturPath, Size size);
    ~Sprite();

    void start() override;

    void setCrop(DDRect src) { _rectSrc = src; }

    static std::shared_ptr<Sprite> create(const char *texturPath, Size size, res::DDTextureFilter filter = res::DDTextureFilter::Nearest);
    static DDRef create(const char *path, Size size, res::DDTexture tex);

    void render() override;
  };
} // namespace dudis