#pragma once

#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/utils/types.h"
#include <algorithm>
#include <iostream>

namespace dudis {

class Motion {
protected:
  float _duration; // quanto tempo deve durar
  float _elapsed;  // quanto tempo já passou
  bool _start = false;
  std::shared_ptr<Entity> _target;

public:
  Motion(const float &duration)
      : _duration(duration), _elapsed(0), _target(nullptr) {}
  ~Motion() = default;

  virtual void update(float t) = 0;

  virtual void startWithTarget(std::shared_ptr<Entity> target) {
    _target = target;
    _elapsed = 0;
  }

  virtual void step() {
    float deltaTime = GetFrameTime();
    _elapsed += deltaTime;
    float t = std::min(_elapsed / _duration, 1.0f);
    update(t);
  }

  virtual void resetSteps() { _elapsed = 0; };

  const float &getDuration() { return _duration; }

  virtual bool isDone() { return _elapsed >= _duration; }
};
} // namespace dudis