#pragma once

#include "dudis2d/core/component/physicsComponent/body/body.h"
#include "dudis2d/core/utils/types.h"
#include <box2d/box2d.h>
#include <dudis2d/core/component/component.h>
#include <functional>

namespace dudis {

class Entity;

class PhysicsComponent : public Component {
protected:
  b2Body *body = nullptr;
  b2World *world = nullptr;
  Entity *owner = nullptr;
  std::shared_ptr<Body> nBody;
  std::function<void(const std::string name)> callbackCollider;

  static constexpr float PIXELS_TO_METERS = 100.0f;
  static constexpr float METERS_TO_PIXELS = 1.0f / PIXELS_TO_METERS;

public:
  PhysicsComponent(b2World *w, Entity *owner) : world(w), owner(owner) {}

  ~PhysicsComponent() {
    callbackCollider = nullptr;
    // puts("indo apagar");
    // if (body && world) {
    //   puts("apagando");
    //   printf("body->GetWorld(): %p\n", body->GetWorld());
    //   printf("world:           %p\n", world);

    //   std::cout << world->GetBodyCount() << "\n";
    //   world->DestroyBody(body);
    //   body = nullptr;
    // }
    // puts("apaguei");
  }

  std::function<void(const b2BodyDef &bodyDef)> configureBodyDef;

  // void createBoxBody(bool isStatic = false, dudis::SizeI sizeBox);

  void setPhysicsBody(std::shared_ptr<Body> body);

  void createBoxBody(const SizeI &sizeBox, bool isStatic = false,
                     bool rotate = false);

  // Sincronizar posição do corpo físico com Entity
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

  static std::shared_ptr<PhysicsComponent> create(Entity *ownerModel);

  static std::shared_ptr<PhysicsComponent>
  createBoxPhysics(Entity *owner, bool isStatic = false, bool rotate = true,
                   SizeI sizeBox = {0, 0});
};
} // namespace dudis