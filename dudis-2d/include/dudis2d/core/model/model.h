#pragma once

#include "dudis2d/core/physicsComponent/physicsComponent.h"
#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/core/utils/types.h"
#include "dudis2d/graphics/renderable.h"
#include "dudis2d/graphics/utils/animatedList/animatedList.h"
#include "dudis2d/scenes/scene/scene.h"
#include "dudis2d/scenes/sceneProperty/sceneProperty.h"
#include <memory>

class Scene;

namespace dudis {
class DDModel {
private:
  // std::shared_ptr<AnimatedList> animated;

protected:
  bool flippedX;
  Vec2 pos{0, 0};
  float angle{0.0f};
  dudis::SizeI size{0, 0};
  std::string name{""};
  SceneProperty sceneProps;

  std::shared_ptr<Renderable> renderable = nullptr;
  std::shared_ptr<PhysicsComponent> physicsComponent = nullptr;
  std::shared_ptr<AnimatedList> animated = nullptr;

public:
  DDModel() : pos{0, 0}, angle(0.0f), size{0, 0}, name("") {}
  virtual ~DDModel();

  virtual void start() {};
  virtual void update() {
    if (physicsComponent && physicsComponent->hasBody()) {
      physicsComponent->syncFromPhysics();
    }
  };

  virtual void onCheckCollider() {}

  virtual void release();

  virtual void onDestroyer() {
    sceneProps.onDelete = true;
    this->renderable->getSceneProps().onDelete = true;
  }

  template <typename T> void addComponent(std::shared_ptr<T> component);

  PhysicsComponent *getPhysicsComponent() { return physicsComponent.get(); }

  const SceneProperty &getSceneProps() const { return sceneProps; }

  std::shared_ptr<Renderable> &getRenderable();
  void render();
  void move(Vec2 delta);
  void setFlippedX(bool flip) { flippedX = flip; }

  Vec2 getMovementInput();
  Vec2 &getPos() { return pos; }
  const SizeI &getSize() const { return size; }
  const float &getAngle() { return angle; }
  void setAngle(const float &nAngle) { angle = nAngle; }
  void setPos(const Vec2 &nPos) { pos = nPos; }
  void setSize(const SizeI &nSize) { size = nSize; }

  AnimatedList *getAnimated() { return animated.get(); }

  // const char *getName() { return name; }

  const std::string &getName() const { return name; }

  static std::shared_ptr<DDModel> create();

  friend class PhysicsComponent;
};

template <typename T> void DDModel::addComponent(std::shared_ptr<T> component) {
  std::cout << "verificando de if passa\n";
  if constexpr (std::is_same<T, Renderable>::value) {
    this->renderable = component;
    std::cout << "if passou Renderable\n";
    this->renderable->setSize({size.w, size.h});
  } else if constexpr (std::is_same<T, PhysicsComponent>::value) {
    this->physicsComponent = component;
    std::cout << "if passou - PhysicsComponent\n";
  } else if constexpr (std::is_same<T, AnimatedList>::value) {
    this->animated = component;
    std::cout << this->animated->Animations().size() << "\n";
    std::cout << "if passou - AnimatedLists\n";
  }
}

} // namespace dudis
