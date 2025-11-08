#include "scenes/scene-camera/scene-camera.h"
#include <algorithm>
#include <cmath>

DD_NAMESPACE;

DD_RENDER;

void SceneCamera::start() {
  this->label = "camera";

  auto bloco = DDRectangle::create({200, 200}, {0, 0});

  bloco->setColor(PURPLE);

  this->addToRender(bloco);
}
void SceneCamera::update() {
  auto &camera = App::getWindow()->getGlobalCamera();

  // Movimento lateral
  if (IsKeyDown(KEY_A))
    camera.traslateTarget({10, 0});
  if (IsKeyDown(KEY_D))
    camera.traslateTarget({-10, 0});

  float wheel = GetMouseWheelMove();

  if (wheel != 0.0f) {
    printf("Scroll movido: %.2f\n", wheel);
  }
}
