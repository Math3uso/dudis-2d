#include "dudis2d/graphics/frameBuffer/frameBuffer.h"

using namespace std;
using namespace dudis;

FrameBuffer::FrameBuffer(SizeI size) : Renderable() {
  this->size = size;
  color = WHITE;

  texture = LoadRenderTexture(size.w, size.h);

  drawCall = []() {};
}

void FrameBuffer::draw(function<void()> callback) { this->drawCall = callback; }

void FrameBuffer::render() {

  DrawTextureRec(texture.texture, (Rectangle){0, 0, size.w, -size.h},
                 (Vector2){pos.x, pos.y}, WHITE);
}

void FrameBuffer::makeFrameBuffer() {
  BeginTextureMode(texture);
  drawCall();
  EndTextureMode();
}