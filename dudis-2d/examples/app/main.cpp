#define DD_DEBUG_MODE 1

#include "dudis2d/dudis2d.h"
#include "scenes/scene-camera/scene-camera.h"
#include "scenes/scene-layout/sceneLayout.h"
#include "scenes/scene-reso/scene-reso.h"
#include "scenes/scene-scenes/scene-scn.h"
#include "scenes/scene1.h"
#include "scenes/scene2/scene2.h"
#include <iostream>

using namespace std;
using namespace dudis;

int main() {

  // SetConfigFlags(FLAG_WINDOW_RESIZABLE);

  Window window(SizeI(800, 600), "Janela");

  window.keepWindowCentered(true);

  Resolution resolution = Resolution({800, 600}, ResolutionPolicy::Letterbox);

  window.setResolution(resolution);

  auto camera = DDCamera();
  // camera.setOffset({400, 300});
  // camera.setTarget({400, 300});

  // camera.setDebugOptions(CameraDebugOptions{
  //     .drawCameraTarget = true,
  //     .drawCameraOffset = true,
  // });

  window.setGlobalCamera(camera);

  SceneManager manager;

  // auto scene1 = Scene1::create();
  // auto scene2 = Scene2::create();
  // auto sceneLayout = SceneLayout::create();
  // auto sceneSla = SceneSla::create();
  // auto sceneReso = SceneReso::create();
  // auto sceneCamera = SceneCamera::create();

  auto sceneScn = SceneScn::create();

  manager.pushScene(move(sceneScn));

  App::setSceneManager(manager);

  window.SetRenderManager(manager);

  window.Running();

  return 0;
}