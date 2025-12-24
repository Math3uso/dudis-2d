#include "dudis2d/graphics/renderable.h"
#include "dudis2d/graphics/renderQueue/renderQueue.h"

using namespace std;
using namespace dudis;

void Renderable::buildRenderCommands(RenderQueue *queue) {
  this->getGlobalMatrix();

  auto gPos = this->getGlobalPos();
  auto gRotation = this->getGlobalRotation() * RAD2DEG;
  auto gScale = this->getGlocalScale();
  auto finalSize = Size(size.w * gScale.x, size.h * gScale.y);

  DrawCommand cmd;
  cmd.pos = gPos;
  cmd.size = finalSize;
  cmd.origin = origin;
  cmd.rotation = gRotation;
  cmd.scale = gScale;
  cmd.src = DDRect{0, 0, 0, 0};
  cmd.tex = 0;
  cmd.type = DDPrimitiveType::Fill;
  cmd.color = color;
  cmd.z = _zOrder;

  queue->addCommand(cmd);

  for (auto &child : _children) {
    child->buildRenderCommands(queue);
  }
}