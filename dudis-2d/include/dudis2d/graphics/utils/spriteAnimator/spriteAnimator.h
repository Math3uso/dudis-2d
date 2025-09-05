#pragma once

#include "dudis2d/graphics/sprites/sprite/sprite.h"

namespace dudis {

class SpriteAnimator : public Renderable
{
protected:
  std::shared_ptr<Sprite> sprite;
  int totalFrames = 0;
  int currentFrame = 0;
  float frameTime = 0.1f; // seconds
  float timer = 0.0f;
  SizeI frameSize;

  bool loop = true;

public:
  SpriteAnimator(std::shared_ptr<Sprite>);

  void update() override;
  void render() override;

  void reset();
  void setLoop(bool enable);
  void setAnimation(int total, SizeI size, float fps);

  void setSize(SizeI size) override;
  void setPos(Vec2 pos) override;
  void setFlippedX(bool flip) override;

  const std::shared_ptr<Sprite> &getSpriteRef() const {
    return sprite;
  };

  std::function<void()> onAnimationEnd = nullptr;

  static std::shared_ptr<SpriteAnimator>
  create(std::shared_ptr<Sprite> spriteRef);
};
} // namespace dudis