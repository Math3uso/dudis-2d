#include "dudis2d/core/component/physicsComponent/debugDraw/debugDraw.h"

using namespace dudis;

DebugDraw::DebugDraw()
{
  // Definir flags do que queremos desenhar
  // SetFlags(e_shapeBit | e_jointBit | e_centerOfMassBit | e_aabbBit);

  SetFlags(e_shapeBit);
}

void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                            const b2Color &color)
{
  (void)vertices;
  (void)vertexCount;
  (void)color;
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                 const b2Color &color)
{
  (void)vertices;
  (void)vertexCount;
  (void)color;
}

void DebugDraw::DrawCircle(const b2Vec2 &center, float radius,
                           const b2Color &color)
{
  (void)center;
  (void)radius;
  (void)color;
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float radius,
                                const b2Vec2 &axis, const b2Color &color)
{
  (void)center;
  (void)radius;
  (void)axis;
  (void)color;
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color)
{
  (void)p1;
  (void)p2;
  (void)color;
}

void DebugDraw::DrawTransform(const b2Transform &xf)
{
  (void)xf;
}

void DebugDraw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color)
{
  (void)p;
  (void)size;
  (void)color;
}
