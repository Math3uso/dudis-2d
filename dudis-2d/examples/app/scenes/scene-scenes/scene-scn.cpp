#include "scenes/scene-scenes/scene-scn.h"
#include "scenes/scene-camera/scene-camera.h"
#include "scenes/scene2/scene2.h"

DD_NAMESPACE
DD_RENDER

void SceneScn::start() {
  this->label = "Scene Scene";

  auto bt = Button::create("next");
  bt->setPos({100, 100});

  auto bt2 = Button::create("prev");
  bt2->setPos({250, 100});

  auto bt3 = Button::create("scenes ");
  bt3->setPos({380, 100});

  bt3->addEventListnear([=](RenderUI *ref) {
    int total = App::getSceneManager().getTotalScenes();
    bt3->setString("scenes: " + std::to_string(total));
  });

  bt->addEventListnear([=](RenderUI *ref) {
    App::getSceneManager().popScene();
    auto sceneCamera = Scene2::create();
    App::getSceneManager().pushScene(move(sceneCamera));
  });

  bt2->addEventListnear(
      [=](RenderUI *ref) { App::getSceneManager().popScene(); });

  this->addToRender(bt);
  this->addToRender(bt2);
  this->addToRender(bt3);
}

void SceneScn::update() {}