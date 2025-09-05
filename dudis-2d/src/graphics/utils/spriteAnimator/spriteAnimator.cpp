#include "dudis2d/graphics/utils/spriteAnimator/spriteAnimator.h"

using namespace dudis;
using namespace std;

SpriteAnimator::SpriteAnimator(shared_ptr<Sprite> sprite) {
  this->sprite = sprite;
}

void SpriteAnimator::setAnimation(int total, SizeI size, float fps) {
  totalFrames = total;
  frameSize = size;
  frameTime = 1.0f / fps;

  sprite->setCrop({0, 0, (float)frameSize.w, (float)frameSize.h});
}

void SpriteAnimator::update() {

  if (!loop)
    return;

  float deltaTime = GetFrameTime();

  timer += deltaTime;

  if (timer >= frameTime) {
    timer = 0.0f;
    currentFrame++;

    if (currentFrame >= totalFrames) {
      if (loop) {
        currentFrame = 0;
        if (onAnimationEnd) {
          std::cout << "Animação chegou no fim\n";
          onAnimationEnd();
        }
      }
      else
        currentFrame = totalFrames - 1;
    }

    float frmae = currentFrame * frameSize.w;

    // cout << "current frame -> " << frmae << "\n";

    sprite->setCrop({frmae, 0, (float)frameSize.w, (float)frameSize.h});
  }
}

void SpriteAnimator::render() {
  if (loop) {
    sprite->render();
  }
}

void SpriteAnimator::reset() {
  currentFrame = 0;
  timer = 0.0f;
}

void SpriteAnimator::setLoop(bool enable) {
  loop = enable;
}

shared_ptr<SpriteAnimator>
SpriteAnimator::create(shared_ptr<Sprite> spriteRef) {
  return make_shared<SpriteAnimator>(spriteRef);
}

void SpriteAnimator::setPos(Vec2 pos) {
  this->pos = pos;
  this->sprite->setPos(pos);
}

void SpriteAnimator::setSize(SizeI size) {
  this->size = size;
  this->sprite->setSize(size);
}

void SpriteAnimator::setFlippedX(bool flip) {
  this->flippedX = flip;
  this->sprite->setFlippedX(flip);
}