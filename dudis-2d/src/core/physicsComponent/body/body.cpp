#include "dudis2d/core/physicsComponent/body/body.h"

using namespace dudis;

Body::Body(const SizeI &size, bool isDinamic) {
  bodyDef.type = isDinamic ? b2_dynamicBody : b2_staticBody;
  this->size = size;
  this->offset = {0.0, 0.0};
}

void Body::setPhysicsDef(PhysicsDef def) {
  fixtureDef.density = def.density;
  fixtureDef.friction = def.friction;
  fixtureDef.restitution = def.restitution;
  fixtureDef.isSensor = def.isSensonr;
}

void Body::rotate(bool isRotate) { bodyDef.fixedRotation = !isRotate; }

void Body::setPos(const Vec2 &nPos) {
  bodyDef.position.Set(nPos.x * METERS_TO_PIXELS, nPos.y * METERS_TO_PIXELS);
  // pos = nPos;
}

void Body::setShape(const PhysicsShape &nShape) {
  auto shape = std::make_shared<PhysicsShape>(nShape);
  this->shapes.push_back(nShape);
}