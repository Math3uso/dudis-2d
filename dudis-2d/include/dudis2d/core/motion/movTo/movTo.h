#pragma once

// #include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/motion/motion.h"

namespace dudis {

class Entity;

class MoveTo : public Motion {
protected:
  Vec2 _startPos;
  Vec2 _endPos;
  Vec2 _initialPos;

public:
  MoveTo(const float duration, const Vec2 &endPos)
      : Motion(duration), _endPos(endPos) {}
  void startWithTarget(std::shared_ptr<Entity> target) override;
  void update(float t) override;

  void resetSteps() override;

  static std::shared_ptr<MoveTo> create(const float &duration,
                                        const Vec2 &endPos,
                                        std::shared_ptr<Entity> entity);
};
} // namespace dudis