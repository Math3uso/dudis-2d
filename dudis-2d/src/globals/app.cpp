#include "dudis2d/globals/app.h"
#include "dudis2d/core/window/window.h"
#include "dudis2d/scenes/sceneManager/sceneManager.h"

float App::deltaTime = 0.f;
Window *App::window = nullptr;
SceneManager *App::sceneManager = nullptr;
std::function<void()> App::windowCallback = []() {};
double App::fixedDt = 1.0f / 60.f;

void App::setWindow(Window &nWindow)
{

  assert(!window && "Window already set");

  window = &nWindow;

  return;
}

Window *App::getWindow() { return window; };

void App::setSceneManager(SceneManager &nManager)
{
  sceneManager = &nManager;
  return;
}

void App::setFrameBufferId(int id, const char *label)
{
}

void App::release()
{
  window = nullptr;
  sceneManager = nullptr;
}