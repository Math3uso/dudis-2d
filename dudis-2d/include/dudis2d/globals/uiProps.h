#include "dudis2d/core/utils/types.h"

class UIProps {
public:
  static void setFontDefault(Font font);
  static const Font &getGlobalFont() { return _font; }

private:
  static Font _font;
  static void _loadFontDefault();
};