#include "dudis2d/core/motion/movBy/moveby.h"

using namespace dudis;
using namespace std;

void MoveBy::update(float t) {
  if (!_start) {
    _startPos = _target->getPos();
    _initialPos = _startPos;
    _start = true;
  }

  Vec2 newPos;
  newPos.x = _startPos.x + _delta.x * t;
  newPos.y = _startPos.y + _delta.y * t;

  _target->setPos(newPos);
}

void MoveBy::resetSteps() {
  cout << "Resetting MoveBy\n";
  _elapsed = 0;
  _target->setPos(_initialPos);
}

std::shared_ptr<MoveBy> MoveBy::create(float d, const Vec2 &delta,
                                       std::shared_ptr<Entity> target) {
  auto moveBy = make_shared<MoveBy>(d, delta);

  moveBy->startWithTarget(target);

  return moveBy;
}