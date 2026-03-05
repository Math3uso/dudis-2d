#include "dudis2d/graphics/renderable.h"
#include "dudis2d/graphics/renderQueue/renderQueue.h"

using namespace std;
using namespace dudis;

void Renderable::buildRenderCommands(RenderQueue *queue)
{
  this->getGlobalMatrix();

  auto gPos = this->getGlobalPos();
  auto gRotation = this->getGlobalRotation() * RAD2DEG;
  auto gScale = this->getGlocalScale();
  auto finalSize = SizeF(size.w * gScale.x, size.h * gScale.y);

  DrawCommand cmd;
  cmd.pos = gPos;
  cmd.size = finalSize;
  cmd.origin = origin;
  cmd.rotation = gRotation;
  cmd.scale = gScale;
  cmd.src = DDRect{0, 0, 0, 0};
  // cmd.tex = 0;
  cmd._tex = _tex;
  cmd.type = DDPrimitiveType::Fill;
  cmd.batch = DDBatchType::Shapes;
  cmd.color = color;
  cmd.z = _zOrder;

  if (_tex)
  {
    // cmd.dest = _rectDest;
    cmd.src = _rectSrc;
    cmd.batch = DDBatchType::Textures;
    cmd.rlTex = *_rlTex;
  }

  queue->addCommand(cmd);

  for (auto &child : _children)
  {
    child->buildRenderCommands(queue);
  }
}

const res::DDTexture Renderable::getTexture() const
{
  res::DDTexture ddtex;
}