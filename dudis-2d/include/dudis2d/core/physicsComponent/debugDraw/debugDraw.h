// debugDraw.h
#pragma once
#include "box2d/box2d.h"
#include "raylib.h"
#include <vector>

namespace dudis {
class DebugDraw : public b2Draw {
private:
  // Conversão física
  static constexpr float PIXELS_TO_METERS = 100.0f;
  static constexpr float METERS_TO_PIXELS = 1.0f / PIXELS_TO_METERS;

  Vector2 metersToPixels(const b2Vec2 &meters) const {
    return {meters.x * PIXELS_TO_METERS, meters.y * PIXELS_TO_METERS};
  }

public:
  DebugDraw();

  // Métodos obrigatórios da b2Draw
  void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                   const b2Color &color) override;
  void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                        const b2Color &color) override;
  void DrawCircle(const b2Vec2 &center, float radius,
                  const b2Color &color) override;
  void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis,
                       const b2Color &color) override;
  void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                   const b2Color &color) override;
  void DrawTransform(const b2Transform &xf) override;
  void DrawPoint(const b2Vec2 &p, float size, const b2Color &color) override;
};
} // namespace dudis