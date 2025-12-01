#include "dudis2d/graphics/ui/text/text.h"

using namespace dudis;
using namespace std;

Text::Text(const std::string &content, int size, shared_ptr<DDFont> font) {

  if (font) {
    _font = font;
  }

  pos = {20, 20};
  TextColor = WHITE;
  fontSize = size;
  text = content;
}

void Text::render() {
  if (!visible)
    return;

  if (_font == nullptr) {
    DrawText(text.c_str(), pos.x, pos.y, fontSize, TextColor);
    return;
  }
  // DrawTextEx(_font->getFont(), text.c_str(), pos.x, pos.y, fontSize,
  // TextColor);
  DrawTextEx(_font->getFont(), text.c_str(), pos, fontSize, 1, TextColor);
}

std::shared_ptr<Text> Text::create(const std::string &content, int size,
                                   shared_ptr<DDFont> font) {

  // Scope<Text> text = CreateScope<Text>(content, size);

  auto text = std::make_shared<Text>(content, size, font);

  return text;
}