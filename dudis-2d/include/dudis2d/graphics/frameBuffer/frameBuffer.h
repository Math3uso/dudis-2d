#pragma once

#include "dudis2d/graphics/renderable.h"
#include <functional>
#include <raylib.h>

namespace dudis {
class FrameBuffer : public Renderable {
protected:
  RenderTexture2D texture = {};

  std::function<void()> drawCall;

public:
  FrameBuffer(SizeI size);

  ~FrameBuffer() {
    if (texture.id > 0) {
      puts("frameBuffer deletado [FRAMEBUFFER]");
      UnloadRenderTexture(texture);
    }
  }

  void render() override;
  void update() override {};

  virtual void draw(std::function<void()> callback);

  void makeFrameBuffer();

  RenderTexture2D &getTexture() { return texture; }

  static std::shared_ptr<FrameBuffer> create(SizeI size) {
    auto frameBuffer = std::make_shared<FrameBuffer>(size);
    return frameBuffer;
  }
};
} // namespace dudis