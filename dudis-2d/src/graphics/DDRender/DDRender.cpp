#include "dudis2d/graphics/DDRender/DDRender.h"

using namespace std;
using namespace dudis;

void DDRender::draw(const DrawCommand &cmd) {
  if (cmd.type == DDPrimitiveType::Fill) {
    Rectangle rect;

    rect.width = cmd.size.w;
    rect.height = cmd.size.h;
    rect.x = cmd.pos.x;
    rect.y = cmd.pos.y;

    DrawRectanglePro(rect, (Vector2)cmd.origin, cmd.rotation, cmd.color);
  } else if (cmd.type == DDPrimitiveType::Lines) {
    DrawRectangleLines(cmd.pos.x, cmd.pos.y, cmd.size.w, cmd.size.h, cmd.color);
  }
}