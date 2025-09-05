#include "dudis2d/core/physicsComponent/physicsComponent.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/core/model/model.h"

using namespace dudis;
using namespace std;

shared_ptr<PhysicsComponent> PhysicsComponent::create(DDModel *ownerModel) {

  auto physicsWorld = App::getPhysicsWorld();

  auto component = std::make_shared<PhysicsComponent>(physicsWorld, ownerModel);
  return component;
}

void PhysicsComponent::createBoxBody(SizeI sizeBox, bool isStatic,
                                     bool rotate) {
  if (!world)
    return;

  if (!world || !owner)
    return;

  b2BodyDef bodyDef;
  bodyDef.type = isStatic ? b2_staticBody : b2_dynamicBody;
  bodyDef.position.Set(owner->pos.x * METERS_TO_PIXELS,
                       owner->pos.y * METERS_TO_PIXELS);

  bodyDef.fixedRotation = !rotate;

  body = world->CreateBody(&bodyDef);

  body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this->owner);

  b2PolygonShape boxShape;
  float halfWidth = (sizeBox.w * METERS_TO_PIXELS) / 2.0f;
  float halfHeight = (sizeBox.h * METERS_TO_PIXELS) / 2.0f;
  boxShape.SetAsBox(halfWidth, halfHeight);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &boxShape;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  fixtureDef.restitution = 0.3f;

  body->CreateFixture(&fixtureDef);
}

std::shared_ptr<PhysicsComponent>
PhysicsComponent::createBoxPhysics(DDModel *owner, bool isStatic, bool rotate,
                                   SizeI sizeBox) {
  {
    auto physicsWorld = App::getPhysicsWorld();

    if (!physicsWorld) {
      std::cerr << "physicsWorld é nullptr! Programa encerrado." << std::endl;
      std::exit(EXIT_FAILURE);
    }
    auto physics = std::make_shared<PhysicsComponent>(physicsWorld, owner);

    sizeBox.w = sizeBox.w == 0 ? owner->getSize().w : sizeBox.w;
    sizeBox.h = sizeBox.h == 0 ? owner->getSize().h : sizeBox.h;

    // sizeBox.w = owner->getSize().w;
    // sizeBox.h = owner->getSize().h;

    physics->createBoxBody(sizeBox, isStatic, rotate);
    return physics;
  }
}

std::shared_ptr<Body> PhysicsComponent::createBody(SizeI size, bool isDinamic) {
  auto body = std::make_shared<Body>(size, isDinamic);
  body->getPhysicsDef().density = 1.0f;
  body->getPhysicsDef().friction = 0.3f;
  body->getPhysicsDef().restitution = 0.3f;
  return body;
}

void PhysicsComponent::setPhysicsBody(shared_ptr<Body> _body) {
  this->nBody = _body;

  this->body = nBody->getBody();

  Vec2 pos = owner->getPos();

  auto size = nBody->getSize();
  auto offset = nBody->getOffset();
  std::cout << "Size: " << size.w << "," << size.h << " Offset: " << offset.x
            << "," << offset.y << std::endl;

  // pos.x == 0 ? owner->getPos().x : pos.x;
  // pos.y == 0 ? owner->getPos().y : pos.y;

  nBody->getBodyDef().position.Set(pos.x * METERS_TO_PIXELS,
                                   pos.y * METERS_TO_PIXELS);

  body = world->CreateBody(&nBody->getBodyDef());

  // dudis::Log::Info("corpo add no mundo");

  body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this->owner);

  // dudis::Log::Info("GetUserData recebeu o owner");

  b2PolygonShape boxShape;
  float halfWidth = (nBody->getSize().w * METERS_TO_PIXELS) / 2.0f;
  float halfHeight = (nBody->getSize().h * METERS_TO_PIXELS) / 2.0f;

  b2Vec2 _offset = {nBody->getOffset().x / PIXELS_TO_METERS,
                    nBody->getOffset().y / PIXELS_TO_METERS};

  boxShape.SetAsBox(halfWidth, halfHeight, _offset, 0.0);

  nBody->getPhysicsDef().shape = &boxShape;

  body->CreateFixture(&nBody->getPhysicsDef());

  const auto &shapes = nBody->getShapes();
  for (const auto &shape : shapes) {
    body->CreateFixture(&shape.fixtureDef);
  }
}

// Sincronização automática
void PhysicsComponent::syncFromPhysics() {
  if (!body || !owner) {
    cout << "body ou Model nullptr";
    return;
  }

  // cout << "atualizando posições\n";

  b2Vec2 bodyPos = body->GetPosition();
  owner->getPos().x = bodyPos.x * PIXELS_TO_METERS;
  owner->getPos().y = bodyPos.y * PIXELS_TO_METERS;
  owner->getAngle() = body->GetAngle() * RAD2DEG;
}

void PhysicsComponent::syncToPhysics() {
  if (!body || !owner)
    return;

  body->SetTransform(b2Vec2(owner->getPos().x * METERS_TO_PIXELS,
                            owner->getPos().y * METERS_TO_PIXELS),
                     owner->getAngle() * DEG2RAD);
}

void PhysicsComponent::setPhysicsPosition(Vec2 position) {
  if (body && owner) {
    body->SetTransform(
        b2Vec2(position.x * METERS_TO_PIXELS, position.y * METERS_TO_PIXELS),
        owner->getAngle() * DEG2RAD);
    // Atualizar owner também
    owner->getPos() = position;
  }
}

// Utilitários
void PhysicsComponent::applyForce(Vec2 force) {
  if (body) {
    body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
  }
}

void PhysicsComponent::applyImpulse(Vec2 impulse) {
  if (body) {
    body->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), true);
  }
}

void PhysicsComponent::setVelocity(Vec2 velocity) {
  if (body) {
    Vec2 velo;
    velo.x = velocity.x == 0 ? this->getPhysicsVelocity().x : velocity.x;
    velo.y = velocity.y == 0 ? this->getPhysicsVelocity().y : velocity.y;
    body->SetLinearVelocity(b2Vec2(velo.x, velo.y));
  }
}

Vec2 PhysicsComponent::getPhysicsVelocity() {
  if (body) {
    b2Vec2 vel = body->GetLinearVelocity();
    return {vel.x, vel.y};
  }
  return {0, 0};
}

void PhysicsComponent::setDensity(float density) {
  if (body) {
    for (b2Fixture *f = body->GetFixtureList(); f; f = f->GetNext()) {
      f->SetDensity(density);
    }
    body->ResetMassData();
  }
}

void PhysicsComponent::setFriction(float friction) {
  if (body) {
    for (b2Fixture *f = body->GetFixtureList(); f; f = f->GetNext()) {
      f->SetFriction(friction);
    }
  }
}

void PhysicsComponent::setRestitution(float restitution) {
  if (body) {
    for (b2Fixture *f = body->GetFixtureList(); f; f = f->GetNext()) {
      f->SetRestitution(restitution);
    }
  }
}

void PhysicsComponent::SetTransform(Vec2 nPos) {
  body->SetTransform(
      b2Vec2(nPos.x * METERS_TO_PIXELS, nPos.y * METERS_TO_PIXELS),
      body->GetAngle());
}

void PhysicsComponent::setCallbackCollider(
    function<void(const string)> nCallback) {
  callbackCollider = nCallback;
}