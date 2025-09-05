#pragma once

#include "dudis2d/graphics/ui/renderUI.h"

namespace dudis {
class Text : public RenderUI {
private:
  std::string text;
  int fontSize = 20;
  Font *font = nullptr;
  Color TextColor;

public:
  Text(const std::string &content, int size);
  void setText(const std::string nText) { text = nText; };
  void setTextColor(Color nTextColor) { TextColor = nTextColor; }
  void setFontSize(int nSize) { fontSize = nSize; }
  void render() override;
  void update() override {}
  std::string &getString() { return text; }
  int FontSize() { return fontSize; }
  static std::shared_ptr<Text> create(const std::string &content, int size);
};
} // namespace dudis