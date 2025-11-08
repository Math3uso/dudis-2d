#include "models/player/player.h"
#include "dudis2d/graphics.h"
#include "dudis2d/physics.h"
#include "models/utils/make_animated_player.h"

using namespace dudis;

Player::Player() : DDModel() {}

void Player::start() {
  name = "player";
  size = {50, 50};
  pos = {25, 300};

  auto physicComponent = PhysicsComponent::create(this);
  auto body = PhysicsComponent::createBody({15, 12}, true);
  body->setPhysicsDef(PhysicsDef(1.0f, 4.0f, 0.0f));
  body->rotate(true);
  body->setFixtureOffset({0, 15.f});

  auto shape = PhysicsShape({50, 50}, PhysicsDef(1.0f, 1.0f, 0.0f));

  body->setShape(shape);

  physicComponent->setPhysicsBody(body);
  auto animatedList = MakeAnimatedPlayer();

  this->addComponent<AnimatedList>(animatedList);
  this->addComponent<PhysicsComponent>(physicComponent);
}

void Player::update() {
  DDModel::update();

  auto movement = this->getMovementInput();

  float deltaTime = GetFrameTime();

  this->physicsComponent->setVelocity({movement.x * speed});

  Vector2 velocity = this->physicsComponent->getPhysicsVelocity();

  if (isJump && abs(velocity.y) < 0.1f) {
    isJump = false;
    std::cout << "Parou de pular!\n";
  }

  physicsComponent->setCallbackCollider([&](const std::string name) {
    if (name == "trampoline") {
      auto vel = this->physicsComponent->getBody()->GetLinearVelocity();
      vel.x = 0.f;
      if (vel.y >= 0.f) {
        this->physicsComponent->getBody()->SetLinearVelocity(
            b2Vec2(vel.x, 0.f));
        this->physicsComponent->applyImpulse({0.f, -0.09f});
      }
    }
  });

  if (!isJump) {
    if (movement.x != 0) {
      this->animated->start("run");
      this->setFlippedX(movement.x == -1 ? true : false);
    } else if (movement.x == 0) {
      this->animated->start("indle");
    }
  } else {
    this->animated->start("jump");
  }

  if (IsKeyPressed(KEY_SPACE) && !isJump) {
    this->physicsComponent->setVelocity({0.f, -3.f});
    isJump = true;
  }
}