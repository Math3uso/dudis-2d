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

enum class UIType {
  Content,
  Layout,
};

class RenderUI : public Renderable {
protected:
  bool visible = true;
  bool enabled = true;
  float mrgin = 0.f;
  float borderWidth = 0;
  Color backgroundColor = BLACK;
  Color BorderColor = BLACK;
  std::vector<std::shared_ptr<RenderUI>> children;
  // Direction padding = (0.f, 0.f, 0.f, 0.f);

  UIType type;
  RenderUI *parent;

public:
  float paddingGlobal = 0.f;
  virtual bool contains(Vector2 point) const {
    return point.x >= pos.x && point.x <= pos.x + size.w && point.y >= pos.y &&
           point.y <= pos.y + size.h;
  }
  virtual void render() override = 0;

  virtual void renderByParent();

  void setVisible(bool v) { visible = v; }
  void setEnabled(bool e) { enabled = e; }
  void setBackgroundColor(Color bgColor) { backgroundColor = bgColor; }
  void setBorderColor(Color bColor) { BorderColor = bColor; }
  Color BackgroundColor() { return backgroundColor; }

  void updateChildren();
  virtual void udpateLayout();

  Rectangle getInnerBounds();

  RenderUI *getParent() { return parent; }
  void setParent(RenderUI *nParent) { parent = nParent; }

  void addChildren(std::shared_ptr<RenderUI> child);
  void setPos(dudis::Vec2 nPos) override;
};
} // namespace dudis