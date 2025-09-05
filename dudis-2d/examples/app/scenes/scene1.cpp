#include "scenes/scene1.h"
#include "dudis2d/graphics.h"
#include "models/ground/ground.h"
#include "models/items/apple_item/apple_item.h"
#include "models/player/player.h"
#include "scenes/bg/background.h"
#include "scenes/scene2/scene2.h"
#include <cmath>

using namespace dudis;

void Scene1::start() {

  label = "scene1";

  this->addPhysics();

  this->showPhysicsDebug = true;
  Log::Alert("scene1 criada");

  App::WindowDraw([]() {
    int fps = GetFPS();
    std::string fpsText = "FPS: " + std::to_string(fps);
    DrawText(fpsText.c_str(), 50, 50, 20, WHITE);
  });

  auto ground = Ground::create();
  auto player = Player::create();
  auto item = AppleItem::create();

  auto background = Background();

  auto bt = Button::create("voltar");
  bt->setPos({220, 200});

  bt->addEventListnear([](RenderUI *ref) {
    auto scene1 = Scene2::create();
    App::getSceneManager().popScene();
  });

  this->drawFrameBuffer(background.getFrameBuffer());

  this->addModel(item);
  this->addModel(ground);
  this->addModel(player);
  this->addToRender(bt);
}

void Scene1::update() {}