#include "dudis2d/graphics/ui/text/text.h"

using namespace dudis;

Text::Text(const std::string &content, int size) {
  pos = {20, 20};
  TextColor = BLACK;
  fontSize = size;
  text = content;
}

void Text::render() {
  if (!visible)
    return;

  DrawText(text.c_str(), pos.x, pos.y, fontSize, TextColor);
}

std::shared_ptr<Text> Text::create(const std::string &content, int size) {

  // Scope<Text> text = CreateScope<Text>(content, size);

  auto text = std::make_shared<Text>(content, size);

  return text;
}