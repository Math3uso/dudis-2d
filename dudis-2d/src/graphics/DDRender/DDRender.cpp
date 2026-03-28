// #include "dudis2d/graphics/DDRender/DDRender.h"
#include "dudis2d/graphics/DDRender/DDRender.h"
#include "dudis2d/graphics/ddrlUtils/ddrlUtils.h"

using namespace std;
using namespace dudis;

void DDRender::draw(const std::vector<DrawCommand> &listCmd)
{
  for (auto &cmd : listCmd)
  {
    if (cmd.batch == DDBatchType::Shapes)
    {
      if (cmd.type == DDPrimitiveType::Fill)
      {
        Rectangle rect;
        rect.width = cmd.size.w;
        rect.height = cmd.size.h;
        rect.x = cmd.pos.x;
        rect.y = cmd.pos.y;

        Vector2 rlOrigin;

        rlOrigin.x = cmd.origin.x;
        rlOrigin.y = cmd.origin.y;

        DrawRectanglePro(rect, rlOrigin, cmd.rotation, cmd.color);
      }
      else if (cmd.type == DDPrimitiveType::Lines)
      {
        DrawRectangleLines(cmd.pos.x, cmd.pos.y, cmd.size.w, cmd.size.h,
                           cmd.color);
      }
    }
    else if (cmd.batch == DDBatchType::Textures)
    {

      auto texture = cmd.rlTex;
      auto w = cmd.src.w == 0 ? texture.width : cmd.src.w;
      auto h = cmd.src.h == 0 ? texture.height : cmd.src.h;

      DrawTexturePro(
          texture, Rectangle{0, 0, w, h},
          Rectangle{cmd.pos.x, cmd.pos.y, cmd.size.w, cmd.size.h},
          Vector2{cmd.origin.x, cmd.origin.y}, cmd.rotation, WHITE);
    }
  }
}

void DDRender::setBlendType(BlendType type)
{
}