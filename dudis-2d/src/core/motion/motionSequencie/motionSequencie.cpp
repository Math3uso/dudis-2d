#include "dudis2d/core/motion/motionSequencie/motionSequencie.h"

using namespace dudis;
using namespace std;

void MotionSequencie::update(float t) {
  if (_current >= _motions.size() && _type == MotionType::Linear)
    return;

  if (_current >= _motions.size() && _type == MotionType::RepeatForever) {
    _current = 0;
    // cout << "Reseting MotionSequencie" << "current " << _current << endl;
    this->resetSteps();
    cout << "Reseting MotionSequencie" << "current " << _current << endl;
    cout << "Motions size " << _motions.size() << endl;
  }

  auto &motion = _motions[_current];

  if (!motion->isDone()) {
    motion->step();
  } else {
    cout << "sla\n";
    _current++;
  }
}

// void MotionSequencie::startWithTarget(shared_ptr<Entity> entity) {}

void MotionSequencie::resetSteps() {
  // for (auto &motion : _motions) {
  //   motion->startWithTarget(_target);
  // }
  _elapsed = 0;
  for (auto &motion : _motions) {
    motion->resetSteps();
  }
}

shared_ptr<MotionSequencie>
MotionSequencie::create(initializer_list<shared_ptr<Motion>> motions,
                        MotionType type) {
  auto motionSequencie = make_shared<MotionSequencie>(motions, type);
  return motionSequencie;
}