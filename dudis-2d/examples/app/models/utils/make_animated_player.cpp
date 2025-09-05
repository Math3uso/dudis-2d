#include "models/utils/make_animated_player.h"

#include "dudis2d/graphics.h"

using namespace std;
using namespace dudis;

shared_ptr<AnimatedList> MakeAnimatedPlayer() {
  auto sprite = Sprite::create("../assets/player.png", {50, 50});
  auto animation = SpriteAnimator::create(sprite);

  auto spr_run = Sprite::create("../assets/run.png", {50, 50});
  auto run_animated = SpriteAnimator::create(spr_run);

  auto spr_jump = Sprite::create("../assets/jump.png", {0, 0});
  auto jump_animate = SpriteAnimator::create(spr_jump);

  sprite->setOrigin({25, 25});
  spr_run->setOrigin({25, 25});
  spr_jump->setOrigin({25, 25});

  animation->setAnimation(11, {32, 32}, 16.f);
  run_animated->setAnimation(12, {32, 32}, 16.f);
  jump_animate->setAnimation(1, {32, 32}, 0);

  auto animatedList = AnimatedList::create();
  animatedList->addToList("indle", animation);
  animatedList->addToList("run", run_animated);
  animatedList->addToList("jump", jump_animate);

  animatedList->start("indle");

  return animatedList;
}