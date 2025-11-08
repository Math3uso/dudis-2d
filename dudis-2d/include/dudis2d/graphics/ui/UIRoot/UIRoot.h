#pragma once

#include "dudis2d/graphics/ui/renderUI.h"

namespace dudis {
class UIRoot : public RenderUI {
private:
  RenderTexture2D ui;

public:
  void createLayout();
  void render() override;

  static std::shared_ptr<UIRoot> create();
};
} // namespace dudis