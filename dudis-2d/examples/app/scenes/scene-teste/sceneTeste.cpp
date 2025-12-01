#include "scenes/scene-teste/sceneTeste.h"
#include "raygui.h"
#include "scenes/scene1.h"
#include <cmath>

DD_PHYSICS
DD_RENDER

using namespace dudis;

void SceneTeste::start() {

  label = "SceneTeste";

  auto bloco = DDRectangle::create({200, 200}, {150, 75});
  bloco->setColor(BLUE);

  App::SceneDraw([]() {
    if (GuiButton(Rectangle{210, 10, 100, 50}, "Voltar para Scene1")) {
      auto scene2 = Scene1::create();
      App::getSceneManager().setScene(std::move(scene2));
    }
  });
}

void SceneTeste::update() {}