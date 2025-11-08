#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/motion/movTo/movTo.h"

using namespace dudis;
using namespace std;

void MoveTo::update(float t) {
  if (!_start) {
    _startPos = _target->getPos();
    _initialPos = _startPos;
    _start = true;
  }

  float nPosX = _startPos.x + (_endPos.x - _startPos.x) * t;
  float nPosY = _startPos.y + (_endPos.y - _startPos.y) * t;

  _target->setPos(Vec2{nPosX, nPosY});
  // this->onMotion(t);
}

void MoveTo::startWithTarget(std::shared_ptr<Entity> target) {
  Motion::startWithTarget(target);
  // _startPos = target->getPos();
}

void MoveTo::resetSteps() {
  cout << "Resetting MoveTo\n";
  _elapsed = 0;
  _target->setPos(_initialPos);
}

shared_ptr<MoveTo> MoveTo::create(const float &duration, const Vec2 &endPos,
                                  shared_ptr<Entity> entity) {
  auto moveTo = std::make_shared<MoveTo>(duration, endPos);

  moveTo->startWithTarget(entity);

  return moveTo;
}