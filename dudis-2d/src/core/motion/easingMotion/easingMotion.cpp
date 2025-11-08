#include "dudis2d/core/motion/easingMotion/easingMotion.h"

using namespace dudis;
using namespace std;

void EasingMotion::startWithTarget(std::shared_ptr<Entity> target) {
  _inner->startWithTarget(target);
}

void EasingMotion::update(float d) {
  float easedT = _easingFunc(d);
  _inner->update(easedT);
}

void EasingMotion::step() {
  float deltaTime = GetFrameTime();
  _elapsed += deltaTime;
  float t = std::min(_elapsed / _duration, 1.0f);
  _inner->step();
  this->update(t);
}