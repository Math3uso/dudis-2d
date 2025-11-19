#include "dudis2d/globals/uiProps.h"

using namespace std;
using namespace dudis;

Font UIProps::_font;

void UIProps::_loadFontDefault() {}

void UIProps::setFontDefault(Font font) { _font = font; }