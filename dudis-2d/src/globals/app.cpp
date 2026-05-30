#include "dudis2d/globals/app.h"
#include "dudis2d/platform/window/window.h"
#include "dudis2d/scenes/sceneManager/sceneManager.h"
#include "dudis2d/core/log/log.h"

using namespace dudis;
using namespace ddgl;

float App::deltaTime = 0.f;
Window *App::window = nullptr;
SceneManager *App::sceneManager = nullptr;
std::function<void()> App::windowCallback = []() {};
double App::fixedDt = 1.0f / 60.f;
std::vector<std::function<void()>> App::_mainThreadQueue;
std::mutex App::_queueMutex;
std::shared_ptr<DDRenderDevice> App::renderContext = nullptr;

PlatformWindow *App::_getPlatformWindow()
{
  return window->_getPlatformWindow();
}

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

void App::runOnMainThread(std::function<void()> task)
{
  std::lock_guard<std::mutex> lock(_queueMutex);
  _mainThreadQueue.push_back(task);
}

void App::processMainThreadQueue()
{
  return;
  std::lock_guard<std::mutex> lock(_queueMutex);
  for (auto &task : _mainThreadQueue)
  {
    task();
  }
  _mainThreadQueue.clear();
}

void App::setRenderContext(std::shared_ptr<ddgl::DDRenderDevice> render)
{
  renderContext = render;
}

void App::release()
{

  Log::Alert("[ALERT] release APP");

  renderContext->shutdown();

  window = nullptr;
  sceneManager = nullptr;
}
