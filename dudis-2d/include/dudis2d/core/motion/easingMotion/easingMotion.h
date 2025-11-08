#pragma once

#include "dudis2d/core/motion/easing/easing.h"
#include "dudis2d/core/motion/motion.h"

namespace dudis {
class EasingMotion : public Motion {
private:
  std::shared_ptr<Motion> _inner;
  std::function<float(float)> _easingFunc;

public:
  EasingMotion(std::shared_ptr<Motion> inner,
               std::function<float(float)> easing)
      : Motion(inner->getDuration()), _inner(inner),
        _easingFunc(std::move(easing)) {}

  void startWithTarget(std::shared_ptr<Entity> target) override;

  void update(float d) override;

  void step() override;

  bool isDone() override {
    // if (_inner->isDone()) {
    //   puts("EasingMotion::isDone");
    // } else if (!_inner->isDone()) {
    //   puts("EasingMotion::isNotDone");
    // }
    return _inner->isDone();
  }

  static std::shared_ptr<EasingMotion>
  create(std::shared_ptr<Motion> inner, std::function<float(float)> easing) {
    return std::make_shared<EasingMotion>(inner, easing);
  };
};
} // namespace dudis