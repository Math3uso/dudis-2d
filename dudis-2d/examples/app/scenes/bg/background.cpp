#include "scenes/bg/background.h"

using namespace std;
using namespace dudis;

Background::Background() {

  tile = Sprite::create("../assets/Purple.png", {64, 64});

  int tilesX = (int)ceil(800.f / 64.f);
  int tilesY = (int)ceil(600.f / 64.f);

  frameBuffer = FrameBuffer::create({800, 600});

  frameBuffer->draw([tile = tile, tilesX, tilesY]() {
    for (int y = 0; y < tilesY; y++) {
      for (int x = 0; x < tilesX; x++) {
        tile->setPos({x * 64.f, y * 64.f});
        tile->render();
      }
    }
  });
  // frameBuffer->setColor(GREEN);
}