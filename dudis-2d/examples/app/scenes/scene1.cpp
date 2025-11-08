#include "scenes/scene1.h"
#include "dudis2d/core/motion/motionSequencie/motionSequencie.h"
#include "dudis2d/core/motion/movBy/moveby.h"
#include "dudis2d/core/motion/movTo/movTo.h"
#include "dudis2d/dudis2d.h"
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

  auto bloco = DDRectangle::create({100, 100}, {300, 300});

  this->addToRender(bloco);

  // this->addPhysics();

  // this->showPhysicsDebug = true;
  // Log::Alert("scene1 criada");

  // App::WindowDraw([]() {
  //   int fps = GetFPS();
  //   std::string fpsText = "FPS: " + std::to_string(fps);
  //   DrawText(fpsText.c_str(), 50, 50, 20, WHITE);
  // });

  // auto bloco = DDRectangle::create({100, 100}, {100, 100});

  // auto ground = Ground::create();
  // auto player = Player::create();
  // auto item = AppleItem::create();

  // this->releaseAfterUse([=]() { Log::Alert("scene1 deletada"); });

  // this->addModel(item);
  // this->addModel(ground);
  // this->addModel(player);
  //  this->addToRender(tile);
  //  this->addToRender(bt);
  // this->addToRender(bloco);
}

void Scene1::update() {}