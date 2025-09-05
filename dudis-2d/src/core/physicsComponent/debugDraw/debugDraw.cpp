#include "dudis2d/core/physicsComponent/debugDraw/debugDraw.h"
#include <cmath>

using namespace dudis;

DebugDraw::DebugDraw() {
  // Definir flags do que queremos desenhar
  // SetFlags(e_shapeBit | e_jointBit | e_centerOfMassBit | e_aabbBit);

  SetFlags(e_shapeBit);
}

// Converter b2Color para Raylib Color
Color b2ColorToRaylib(const b2Color &b2color, uint8_t alpha = 255) {
  return {(uint8_t)(b2color.r * 255), (uint8_t)(b2color.g * 255),
          (uint8_t)(b2color.b * 255), alpha};
}

void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount,
                            const b2Color &color) {
  Color raylibColor = b2ColorToRaylib(color);

  // Desenhar linhas conectando os vértices
  for (int i = 0; i < vertexCount; i++) {
    int next = (i + 1) % vertexCount;
    Vector2 p1 = metersToPixels(vertices[i]);
    Vector2 p2 = metersToPixels(vertices[next]);
    DrawLineV(p1, p2, raylibColor);
  }
}

void DebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount,
                                 const b2Color &color) {
  Color fillColor = b2ColorToRaylib(color, 100); // Semi-transparente
  Color outlineColor = b2ColorToRaylib(color);

  // Converter vértices para Raylib
  std::vector<Vector2> points(vertexCount);
  for (int i = 0; i < vertexCount; i++) {
    points[i] = metersToPixels(vertices[i]);
  }

  // Raylib não tem função direta para polígono preenchido
  // Então vamos desenhar triângulos (triangulação simples para convexos)
  if (vertexCount >= 3) {
    for (int i = 1; i < vertexCount - 1; i++) {
      DrawTriangle(points[0], points[i], points[i + 1], fillColor);
    }
  }

  // Desenhar contorno
  DrawPolygon(vertices, vertexCount, color);
}

void DebugDraw::DrawCircle(const b2Vec2 &center, float radius,
                           const b2Color &color) {
  Vector2 centerPixels = metersToPixels(center);
  float radiusPixels = radius * PIXELS_TO_METERS;
  Color raylibColor = b2ColorToRaylib(color);

  DrawCircleLinesV(centerPixels, radiusPixels, raylibColor);
}

void DebugDraw::DrawSolidCircle(const b2Vec2 &center, float radius,
                                const b2Vec2 &axis, const b2Color &color) {
  Vector2 centerPixels = metersToPixels(center);
  float radiusPixels = radius * PIXELS_TO_METERS;
  Color fillColor = b2ColorToRaylib(color, 100); // Semi-transparente
  Color outlineColor = b2ColorToRaylib(color);

  // Círculo preenchido
  DrawCircleV(centerPixels, radiusPixels, fillColor);

  // Contorno
  DrawCircleLinesV(centerPixels, radiusPixels, outlineColor);

  // Linha do eixo (mostra rotação)
  Vector2 axisEnd = {centerPixels.x + axis.x * radiusPixels,
                     centerPixels.y + axis.y * radiusPixels};
  DrawLineV(centerPixels, axisEnd, outlineColor);
}

void DebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2,
                            const b2Color &color) {
  Vector2 point1 = metersToPixels(p1);
  Vector2 point2 = metersToPixels(p2);
  Color raylibColor = b2ColorToRaylib(color);

  DrawLineV(point1, point2, raylibColor);
}

void DebugDraw::DrawTransform(const b2Transform &xf) {
  const float axisScale = 0.4f;
  Color red = RED;
  Color green = GREEN;

  Vector2 p1 = metersToPixels(xf.p);

  // Eixo X (vermelho)
  Vector2 p2 = {p1.x + xf.q.c * axisScale * PIXELS_TO_METERS,
                p1.y + xf.q.s * axisScale * PIXELS_TO_METERS};
  DrawLineV(p1, p2, red);

  // Eixo Y (verde)
  p2 = {p1.x - xf.q.s * axisScale * PIXELS_TO_METERS,
        p1.y + xf.q.c * axisScale * PIXELS_TO_METERS};
  DrawLineV(p1, p2, green);
}

void DebugDraw::DrawPoint(const b2Vec2 &p, float size, const b2Color &color) {
  Vector2 point = metersToPixels(p);
  float sizePixels = size * PIXELS_TO_METERS;
  Color raylibColor = b2ColorToRaylib(color);

  DrawCircleV(point, sizePixels, raylibColor);
}