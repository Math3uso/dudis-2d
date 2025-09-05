#pragma once

#include "dudis2d/graphics/ui/renderUI.h"
#include "dudis2d/graphics/ui/text/text.h"
#include <functional>

namespace dudis {
class Button : public dudis::RenderUI {
protected:
  std::string textStr;
  // dudis::Text text;
  std::shared_ptr<Text> textChild;
  std::function<void(RenderUI *ref)> callback;

public:
  Button(const std::string &str);
  static std::shared_ptr<Button> create(const std::string &str);
  void addEventListnear(std::function<void(RenderUI *ref)> nCallback) {
    callback = nCallback;
  };
  void setString(const std::string &nStr);
  // dudis::Text &Text() { return text; }
  void update() override;
  void render() override;
};
} // namespace dudis