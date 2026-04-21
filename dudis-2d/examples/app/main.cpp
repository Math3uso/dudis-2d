#define DD_DEBUG_MODE 1

#include "dudis2d/dudis2d.h"
// #include "scenes/scene-camera/scene-camera.h"
// #include "scenes/scene-layout/sceneLayout.h"
// #include "scenes/scene-reso/scene-reso.h"
// #include "scenes/scene-scenes/scene-scn.h"
#include "scenes/scene-zorder-bug.h"
#include "scenes/scene1.h"
#include "scenes/scene-bloco.h"
// #include "scenes/scene2/scene2.h"
#include <iostream>

using namespace std;
using namespace dudis;

int main()
{

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  Window window(SizeI(1280, 720), "Janela");

  window.init();

  window.keepWindowCentered(true);

  Resolution resolution = Resolution({800, 600}, ResolutionPolicy::Letterbox);

  window.setResolution(resolution);

  // camera.setOffset({400, 300});
  //  camera.setOffset({400, 300});
  // camera.setTarget({25, 300});

  SceneManager manager;

  // auto scene1 = SceneBloco::create();
  auto scene1 = Scene::create<SceneBloco>();
  // auto scene1 = Scene::create<SceneZOrderBug>();
  //  auto scene2 = Scene2::create();
  //  auto sceneLayout = SceneLayout::create();
  //  auto sceneSla = SceneSla::create();
  //  auto sceneReso = SceneReso::create();
  //  auto sceneCamera = SceneCamera::create();

  // auto sceneScn = SceneScn::create();

  manager.pushScene(move(scene1));

  // manager.setScene(move(scene1));

  App::setSceneManager(manager);

  window.SetRenderManager(manager);

  window.Running();

  return 0;
}
