#pragma once

#include "dudis2d/core/physicsComponent/body/body.h"
#include "dudis2d/core/utils/types.h"
#include <box2d/box2d.h>
#include <functional>

namespace dudis {

class DDModel;

class PhysicsComponent {
protected:
  b2Body *body = nullptr;
  b2World *world = nullptr;
  DDModel *owner = nullptr;
  std::shared_ptr<Body> nBody;
  std::function<void(const std::string name)> callbackCollider;

  static constexpr float PIXELS_TO_METERS = 100.0f;
  static constexpr float METERS_TO_PIXELS = 1.0f / PIXELS_TO_METERS;

public:
  PhysicsComponent(b2World *w, DDModel *ownerModel)
      : world(w), owner(ownerModel) {}

  ~PhysicsComponent() {
    if (body && world) {
      world->DestroyBody(body);
    }
  }

  std::function<void(const b2BodyDef &bodyDef)> configureBodyDef;

  // void createBoxBody(bool isStatic = false, dudis::SizeI sizeBox);

  void setPhysicsBody(std::shared_ptr<Body> body);

  void createBoxBody(const SizeI &sizeBox, bool isStatic = false,
                     bool rotate = false);

  // Sincronizar posição do corpo físico com DDModel
  void syncFromPhysics();

  void syncToPhysics();

  // Utilitários
  void applyForce(Vec2 force);
  void applyImpulse(Vec2 impulse);

  void setVelocity(Vec2 velocity);

  void setPhysicsPosition(Vec2 position);

  bool hasBody() const { return body != nullptr; }
  b2Body *getBody() { return body; }
  void setDensity(const float &density);
  void setFriction(const float &friction);
  void setRestitution(const float &restitution);
  Vec2 getPhysicsVelocity();

  void SetTransform(Vec2 nPos);

  void
  setCallbackCollider(std::function<void(const std::string name)> nCallback);

  std::function<void(const std::string name)> getCallbackCollider() {
    return callbackCollider;
  };

  // void setVelocityY(float veloY);

  static std::shared_ptr<Body> createBody(SizeI size, bool isDinamic);

  static std::shared_ptr<PhysicsComponent> create(DDModel *ownerModel);

  static std::shared_ptr<PhysicsComponent>
  createBoxPhysics(DDModel *owner, bool isStatic = false, bool rotate = true,
                   SizeI sizeBox = {0, 0});
};
} // namespace dudis