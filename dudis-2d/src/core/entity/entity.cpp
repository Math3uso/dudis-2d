#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/motion/motion.h"

using namespace dudis;

void Entity::defaultUpdate() {
  this->update();
  this->runMotions();
}

void Entity::runMotions() {
  if (_action) {
    if (_action->isDone()) {
      _action.reset();
      puts("motion liberada");
    } else {
      _action->step();
    }
  }
  // if (_action && !_action->isDone()) {
  //   _action->step();
  // }
}