#pragma once

#include "dudis2d/core/utils/types.h"
#include "raylib.h"
#include <memory>

namespace dudis {

class DDFont {
private:
  r_Font _font;

public:
  DDFont(const char *fontPath) { _font = LoadFont(fontPath); };

  ~DDFont() {
    puts("liberando font [FONT]");
    UnloadFont(_font);
  }

  const r_Font &getFont() const { return _font; }

  static std::shared_ptr<DDFont> create(const char *fontPath) {
    return std::make_shared<DDFont>(fontPath);
  }
};
} // namespace dudis