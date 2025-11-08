#pragma once

#include "dudis2d/core/motion/motion.h"

namespace dudis {
enum class MotionType { RepeatForever, Linear };

class MotionSequencie : public Motion {
private:
  std::vector<std::shared_ptr<Motion>> _motions;
  size_t _current = 0;
  MotionType _type = MotionType::Linear;
  bool _needsReset = false;

public:
  MotionSequencie(std::initializer_list<std::shared_ptr<Motion>> motions,
                  MotionType type = MotionType::Linear)
      : Motion(0.f), _motions(motions), _type(type) {}

  void startWithTarget(std::shared_ptr<Entity> entity) override {
    _current = 0;
  }

  void resetSteps() override;

  void update(float t) override;

  bool isDone() override {
    return _current >= _motions.size() && _type == MotionType::Linear;
  }

  static std::shared_ptr<MotionSequencie>
  create(std::initializer_list<std::shared_ptr<Motion>> motions,
         MotionType type = MotionType::Linear);
};

} // namespace dudis