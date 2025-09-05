#pragma once
#include <dudis2d/graphics.h>
#include <memory>

using namespace dudis;

class Background {
private:
  std::shared_ptr<Sprite> tile;
  std::shared_ptr<FrameBuffer> frameBuffer;

public:
  Background();
  std::shared_ptr<FrameBuffer> getFrameBuffer() { return frameBuffer; };
};