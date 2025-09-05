#pragma once

#include "dudis2d/core/utils/types.h"
#include "dudis2d/graphics/renderable.h"
#include <vector>

namespace dudis {

class Direction {
public:
  float top;
  float bottom;
  float left;
  float right;

  Direction(float value)
      : top(value), bottom(value), left(value), right(value) {}
};

class RenderUI : public Renderable {
protected:
  bool visible = true;
  bool enabled = true;
  Color backgroundColor = BLACK;
  Color BorderColor = BLACK;
  float borderWidth = 0;
  std::vector<std::shared_ptr<RenderUI>> children;
  // Direction padding;
  float mrgin = 0.f;

public:
  virtual bool contains(Vector2 point) const {
    return point.x >= pos.x && point.x <= pos.x + size.w && point.y >= pos.y &&
           point.y <= pos.y + size.h;
  }
  virtual void render() = 0;
  void setVisible(bool v) { visible = v; }
  void setEnabled(bool e) { enabled = e; }
  void setBackgroundColor(Color bgColor) { backgroundColor = bgColor; }
  void setBorderColor(Color bColor) { BorderColor = bColor; }
  Color BackgroundColor() { return backgroundColor; }
  void updateChildren() {
    for (const auto &child : children) {
      child->setPos({pos.x + child->getPos().x, pos.y + child->getPos().y});
    }
  }
  void setPos(dudis::Vec2 nPos) override {
    pos = nPos;
    updateChildren();
  }
};
} // namespace dudis
