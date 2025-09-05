#include "dudis2d/core/physicsComponent/contactListenear/contactListenear.h"
#include "dudis2d/core/model/model.h"
#include <iostream>

using namespace dudis;

void ContactListner::BeginContact(b2Contact *contact) {
  b2Fixture *fixtureA = contact->GetFixtureA();
  b2Fixture *fixtureB = contact->GetFixtureB();

  b2Body *bodyA = fixtureA->GetBody();
  b2Body *bodyB = fixtureB->GetBody();

  DDModel *modelA = reinterpret_cast<DDModel *>(bodyA->GetUserData().pointer);
  DDModel *modelB = reinterpret_cast<DDModel *>(bodyB->GetUserData().pointer);

  if (modelA && modelB) {
    auto physicsComponentA = modelA->getPhysicsComponent();
    auto physicsComponentB = modelB->getPhysicsComponent();

    auto calbackA = physicsComponentA->getCallbackCollider();
    auto calbackB = physicsComponentA->getCallbackCollider();

    if (calbackA) {
      calbackA(modelB->getName());
    } else if (calbackB) {
      calbackB(modelA->getName());
    }
  }
}

void ContactListner::EndContact(b2Contact *contact) {
  b2Fixture *fixtureA = contact->GetFixtureA();
  b2Fixture *fixtureB = contact->GetFixtureB();
  // std::cout << "Colisão parou entre corpos: " << std::endl;
}