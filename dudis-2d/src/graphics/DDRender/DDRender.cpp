// // #include "dudis2d/graphics/DDRender/DDRender.h"
// #include "dudis2d/graphics/DDRender/DDRender.h"
// // #include "dudis2d/graphics/ddrlUtils/ddrlUtils.h"
// #include "dudis2d/graphics/renderQueue/renderQueue.h"
// #include "dudis2d/platform/ddrlUtils/toRLBlendType.h"
// #include "raylib.h"

// using RLCOLOR = Color;

// using namespace std;

// namespace dudis
// {

//   bool isView = false;
//   int DDRender::_drawCalls = 0;

//   void DDRender::defineRLDrawCalls()
//   {
//     int batch = 0;
//   }

//   void DDRender::draw(const std::vector<DrawCommand> &listCmd, RenderQueue *queue)
//   {
//     // RenderTexture2D
//     // LoadRenderTexture()
//     // UnloadRenderTexture();
//     // BeginTextureMode
//     BlendType currentBlendType = BlendType::AlphaComposite;

// #ifdef DD_DEBUG
//     if (isView == false)
//     {
//       for (auto &cmd : listCmd)
//       {
//         cout << cmd << "\n";
//       }
//     }
//     isView = true;
// #endif

//     for (auto &cmd : listCmd)
//     {
//       switch (cmd.cmdState)
//       {
//       case CommandState::PushScissor:
//       {
//         auto r = cmd.scissorRect;
//         BeginScissorMode(r.x, r.y, r.w, r.h);
//         break;
//       }

//       case CommandState::EndScissor:
//         EndScissorMode();
//         break;

//       default:
//       {

//         if (cmd.blendType != currentBlendType)
//         {
//           BeginBlendMode(ddrlUtils::toRLBlendType(cmd.blendType));
//           currentBlendType = cmd.blendType;
//         }

//         if (cmd.batch == DDBatchType::Shapes)
//         {
//           Rectangle rect;
//           rect.width = cmd.size.w;
//           rect.height = cmd.size.h;
//           rect.x = cmd.pos.x;
//           rect.y = cmd.pos.y;

//           Vector2 rlOrigin;

//           rlOrigin.x = cmd.origin.x;
//           rlOrigin.y = cmd.origin.y;

//           auto color = cmd.color;

//           DrawRectanglePro(rect, rlOrigin, cmd.rotation, RLCOLOR{color.r, color.g, color.b, color.a});
//         }
//         else if (cmd.batch == DDBatchType::Textures)
//         {

//           auto texture = cmd.rlTex;
//           auto w = cmd.src.w == 0 ? texture.width : cmd.src.w;
//           auto h = cmd.src.h == 0 ? texture.height : cmd.src.h;
//           auto ddColor = cmd.color;

//           DrawTexturePro(
//               texture, Rectangle{0, 0, w, h},
//               Rectangle{cmd.pos.x, cmd.pos.y, cmd.size.w, cmd.size.h},
//               Vector2{cmd.origin.x, cmd.origin.y}, cmd.rotation, RLCOLOR{ddColor.r, ddColor.g, ddColor.b, ddColor.a});
//         }
//       }
//       }
//     }
//   }

//   void DDRender::setBlendType(BlendType type)
//   {
//   }

// }
