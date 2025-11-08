#pragma once

#include "dudis2d/core/motion/motion.h"

namespace dudis {
class MoveBy : public Motion {
private:
  Vec2 _delta;
  Vec2 _startPos;
  Vec2 _initialPos;

public:
  MoveBy(const float duration, const Vec2 &delta)
      : Motion(duration), _delta(delta) {}
  void update(float t) override;
  void startWithTarget(std::shared_ptr<Entity> target) {
    Motion::startWithTarget(target);
    // _start -= false;
    _start = false;
  };

  void resetSteps() override;

  static std::shared_ptr<MoveBy> create(float d, const Vec2 &delta,
                                        std::shared_ptr<Entity> target);
};
} // namespace dudis