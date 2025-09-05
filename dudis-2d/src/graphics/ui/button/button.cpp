#include "dudis2d/graphics/ui/button/button.h"
#include <memory>

using namespace dudis;

Button::Button(const std::string &str) : textStr(str) {
  size = {100, 30};
  pos = {15, 15};

  backgroundColor = GRAY;

  dudis::Text text = Text(str, 20);
  text.setPos({pos.x, pos.y / 2});
  // text.setFontSize(20);

  //=========

  textChild = std::make_shared<Text>(text);

  children.push_back(textChild);

  // children.push_back(std::make_shared<Text>(text));
}

void Button::render() {
  if (!visible)
    return;

  DrawRectangleV(pos, {float(size.w), float(size.h)}, backgroundColor);
  // DrawText(text.getString().c_str(), text.getPos().x, text.getPos().y,
  //          text.FontSize(), text.BackgroundColor());

  DrawText(textChild->getString().c_str(),
           static_cast<int>(textChild->getPos().x),
           static_cast<int>(textChild->getPos().y), textChild->FontSize(),
           textChild->BackgroundColor());
}

void Button::update() {
  if (enabled && visible && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
      contains(GetMousePosition())) {
    if (callback) {
      callback(this);
    }
  }
}

std::shared_ptr<Button> Button::create(const std::string &str) {
  // auto nButton = CreateScope<Button>(str);

  auto nButton = std::make_shared<Button>(str);
  return nButton;
}

void Button::setString(const std::string &str) {
  // textStr = str;
  // text.setText(str);

  textChild->setText(str);
}