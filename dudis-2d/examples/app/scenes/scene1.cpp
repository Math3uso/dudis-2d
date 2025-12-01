#include "scenes/scene1.h"
#include "raygui.h"
#include "scenes/scene-teste/sceneTeste.h"
#include <cmath>

DD_PHYSICS

using namespace dudis;

void Scene1::start() {

  label = "scene1";

  // this->addPhysics();
  // showPhysicsDebug = true;

  auto bloco = DDRectangle::create({100, 250}, {100, 50});
  bloco->setColor(RED);
  bloco->setTransformType(TransformType::DisableParentTransform);
  bloco->setOrigin({50, 125});

  auto player = Sprite::create("../assets/player.png", {100, 100});
  player->setCrop({0, 0, 32, 32});

  auto bloco2 = DDRectangle::create({100, 250}, {100, 50});
  // auto teste = PhysicsComponent::createBoxPhysics(bloco.get());

  auto root = DDRectangle::create({800, 600}, {0, 0});
  root->setTransformType(TransformType::DisableParentTransform);
  root->setColor(Color{31, 31, 31, 255});

  this->addChild(player);

  // root->addChild(bloco, 2);
  // root->addChild(bloco2, 1);

  // bloco->addComponent<PhysicsComponent>(teste);

  // auto text = Text::create("Hello Dudis 2D!", 20);
  // text->setPos({300, 300});
  // auto _counter = std::make_shared<int>(0);

  // this->addToRender(bloco);
  // App::SceneDraw([_counter, text]() {
  //   std::string buttonText = "click " + std::to_string(*_counter);
  //   if (GuiButton(Rectangle{10, 10, 100, 100}, buttonText.c_str())) {
  //     *_counter += 1;
  //   }

  //   text->setText("Clicked: " + std::to_string(*_counter) + " times");
  // if (GuiButton(Rectangle{210, 10, 100, 50}, "Next Scene")) {
  //   auto scene2 = SceneTeste::create();
  //   puts("movendo para scene2");
  //   App::getSceneManager().setScene(std::move(scene2));
  // }
  // });

  int *zOrder = new int(0);

  App::WindowDraw([this, root, bloco, zOrder]() {
    // root->addChild(sla);
    if (GuiButton(Rectangle{500, 300, 100, 20}, "Next Scene")) {
      // auto sla = DDRectangle::create({50, 50}, {100, 500});
      // root->addChild(sla);
      *zOrder = *zOrder == 0 ? 10 : 0;
      std::cout << *zOrder << "\n";
      bloco->setZOrder(*zOrder);
    }
  });

  // bloco->addChild(bloco2);

  // this->addToRender(text);
  // this->addToRender(bloco2);
  // this->addToRender(bloco);
  this->addChild(bloco, 0);
  this->addChild(bloco2, 0);
  // this->addChild(root);
}

void Scene1::update() {}