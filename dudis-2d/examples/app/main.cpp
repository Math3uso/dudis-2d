#include "dudis2d/dudis2d.h"
#include "scenes/scene-layout/sceneLayout.h"
#include "scenes/scene1.h"
#include "scenes/scene2/scene2.h"
#include <iostream>

using namespace std;
using namespace dudis;

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  Window window(SizeI(800, 600), "Janela");

  SceneManager manager;

  // auto scene1 = Scene1::create();
  // auto scene2 = Scene2::create();
  auto sceneLayout = SceneLayout::create();

  manager.pushScene(move(sceneLayout));

  App::setSceneManager(manager);

  window.SetRenderManager(manager);

  window.Running();

  return 0;
}