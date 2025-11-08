#pragma once

#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/utils/types.h"

namespace dudis {

class Motion;

class Entity {

protected:
  dudis::SizeI size;
  dudis::Vec2 pos;
  float angle = 0.0f; // in radians
  std::vector<std::shared_ptr<Motion>> actions;
  std::shared_ptr<Motion> _action;

public:
  float getAngle() const { return angle; }
  Vec2 getPos() const { return pos; }
  SizeI getSize() const { return size; }

  virtual void setPos(dudis::Vec2 nPos) { pos = nPos; }
  virtual void setSize(dudis::SizeI nSize) { size = nSize; }
  virtual void translate(dudis::Vec2 nPos) {
    pos.x += nPos.x;
    pos.y += nPos.y;
  }

  virtual void rotate(float nAngle) { angle = nAngle; }
  virtual void update() {};

  void defaultUpdate();

  void runMotions();

  void setMotion(std::shared_ptr<Motion> action) {
    // this->actions.push_back(action);
    _action = action;
  };

  virtual ~Entity() = default;
};
} // namespace dudis