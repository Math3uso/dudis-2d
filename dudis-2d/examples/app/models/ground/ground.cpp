#include "models/ground/ground.h"
#include "dudis2d/graphics.h"
#include "dudis2d/physics.h"

using namespace dudis;

Ground::Ground() : DDModel() {}

void Ground::start() {

  name = "ground";

  size = {650, 30};
  pos = {330, 400};

  auto shape = DDRectangle::create(size, pos);
  shape->setOrigin({325, 14});

  shape->setColor(DARKPURPLE);
  auto body = PhysicsComponent::createBoxPhysics(this, true);

  this->addComponent<Renderable>(shape);
  this->addComponent<PhysicsComponent>(body);
}

void Ground::update() {
  DDModel::update();
}