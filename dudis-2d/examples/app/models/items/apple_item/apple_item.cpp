#include "models/items/apple_item/apple_item.h"
#include "dudis2d/graphics.h"
#include <string>

using namespace std;
using namespace dudis;

AppleItem::AppleItem() : DDModel() {};

void AppleItem::start() {
  pos = {100, 300};
  size = {64, 64};

  // 17

  auto sprite = Sprite::create("../assets/Apple.png", size);
  sprite->setOrigin({32, 32});

  auto collected = Sprite::create("../assets/Collected.png", size);
  collected->setOrigin({32, 32});

  auto animation = SpriteAnimator::create(sprite);
  animation->setAnimation(17, {32, 32}, 20.0f);

  auto animationCollected = SpriteAnimator::create(collected);
  animationCollected->setAnimation(6, {32, 32}, 20.0f);

  auto animatedList = AnimatedList::create();
  animatedList->addToList("item", animation);
  animatedList->addToList("collected", animationCollected);

  animatedList->start("item");

  // auto body = PhysicsComponent::createBoxPhysics(this, true, false, {16,
  // 16});

  auto body = PhysicsComponent::createBody({32, 32}, false);
  body->getPhysicsDef().isSensor = true;
  auto physicsComponent = PhysicsComponent::create(this);
  physicsComponent->setPhysicsBody(body);

  this->addComponent<AnimatedList>(animatedList);
  this->addComponent<PhysicsComponent>(physicsComponent);

  this->physicsComponent->setCallbackCollider([&](std::string name) {
    std::cout << name << "\n";
    if (name == "player") {
      this->animated->start("collected");
      auto animation = this->animated->getCurrentAnimation();

      animation->onAnimationEnd = [&]() {
        // animation->setLoop(false);
        this->animated->stop("collected");
        this->onDestroyer();
      };
    }
  });
}

void AppleItem::update() { DDModel::update(); }