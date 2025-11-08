#pragma once

#include "dudis2d/core/utils/types.h"
#include <box2d/box2d.h>

namespace dudis {

static const float PIXELS_TO_METERS = 100.0f;
static const float METERS_TO_PIXELS = 1.0f / PIXELS_TO_METERS;

class PhysicsDef {
public:
  float density = 0.0;
  float friction = 0.0;
  float restitution = 0.0;
  bool isSensonr = false;

  PhysicsDef(float density, float friction, float restitution)
      : density(density), friction(friction), restitution(restitution) {}
};

class PhysicsShape {
private:
  PhysicsDef physicsDef;
  Vec2 offset = {0.0, 0.0};
  SizeI size;
  const char *_label;
  std::function<void()> callbackColision;

public:
  PhysicsShape(SizeI size, PhysicsDef nDef) : physicsDef(nDef), size(size) {

    float halfWidth = (size.w * METERS_TO_PIXELS) / 2.0f;
    float halfHeight = (size.h * METERS_TO_PIXELS) / 2.0f;

    b2Vec2 _offset = {offset.x / PIXELS_TO_METERS, offset.y / PIXELS_TO_METERS};

    shape.SetAsBox(halfWidth, halfHeight, _offset, 0.0);
    fixtureDef.density = nDef.density;
    fixtureDef.friction = nDef.friction;
    fixtureDef.restitution = nDef.restitution;
    fixtureDef.isSensor = nDef.isSensonr;
    fixtureDef.shape = &shape;
  }

  // void callbackColision()

  void setFixtureOffset(Vec2 nOffset) { offset = nOffset; }
  const Vec2 getOffset() const { return offset; }

  void setLabel(const char *nLabel) { _label = nLabel; }
  const char *getLabel() const { return _label; }

  b2FixtureDef fixtureDef;
  b2PolygonShape shape;
};

class Body {
private:
  b2BodyDef bodyDef;
  b2Body *body = nullptr;
  b2FixtureDef fixtureDef;
  SizeI size;
  Vec2 offset;
  const char *label;
  // std::vector<std::shared_ptr<PhysicsShape>> shapes;
  std::vector<PhysicsShape> shapes;
  static constexpr float PIXELS_TO_METERS = 100.0f;
  static constexpr float METERS_TO_PIXELS = 1.0f / PIXELS_TO_METERS;

public:
  Body(const SizeI &size, bool isDinamic);
  void setPhysicsDef(PhysicsDef def);
  void setShape(const PhysicsShape &nShape);
  // std::vector<std::shared_ptr<PhysicsShape>> &getShapes() { return shapes; }
  std::vector<PhysicsShape> &getShapes() { return shapes; }
  void rotate(bool isRotate);
  void setPos(const Vec2 &pos);

  void setFixtureOffset(Vec2 nOffset) { offset = nOffset; }

  void setLabel(const char *nLabel) { label = nLabel; }
  const char *getLabel() const { return label; }

  b2BodyDef &getBodyDef() { return bodyDef; }
  b2Body *getBody() { return body; }
  b2FixtureDef &getPhysicsDef() { return fixtureDef; }

  SizeI getSize() const { return size; }
  Vec2 getOffset() const { return offset; }
  // Vec2 getPos() const { return pos; }
};
} // namespace dudis