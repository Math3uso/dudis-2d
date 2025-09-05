#include "dudis2d/core/model/model.h"
#include "dudis2d/dudis2d.h"
#include <type_traits>

using namespace dudis;
using namespace std;

void DDModel::render() {

  if (animated) {
    this->renderable = animated->getCurrentAnimation();
  }

  if (renderable) {
    renderable->setPos({pos.x, pos.y});
    renderable->rotate(angle);

    this->renderable->setSize({size.w, size.h});

    this->renderable->setFlippedX(flippedX);

    // this->renderable->render();
  }
}

shared_ptr<Renderable> &DDModel::getRenderable() {
  return this->renderable;
}

DDModel::~DDModel() {
  if (!name.empty()) {
    std::cout << "model " << name << " deletado\n";
  }
  else {
    std::cout << "model sem nome deletado\n";
  }
}

Vec2 DDModel::getMovementInput() {

  Vec2 input{0, 0};

  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    input.x -= 1;
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    input.x += 1;
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    input.y -= 1;
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    input.y += 1;

  return input;
}

void DDModel::move(Vec2 delta) {
  pos = delta;
}

void DDModel::release() {

  // if (this->renderable) {
  //   this->renderable.reset();
  //   Log::Success("Renderable liberado");
  // }
  // else if (this->animated) {
  //   this->animated.reset();
  //   Log::Success("Animated liberado");
  // }

  cout << "total de referencias: " << this->renderable.use_count() << "\n";

  this->renderable.reset();
  this->renderable = nullptr;

  cout << "total de referencias: " << this->animated.use_count() << "\n";

  Log::Success("Renderable liberado");

  this->animated.reset();
  Log::Success("Animated liberado");
  Log::Success("Recursos de DDModel: " + name + " liberados");
}