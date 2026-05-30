#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <vector>
#include <memory>
#include "dudis2d/graphics/ddgl/render/renderDevice.h"

namespace dudis
{
  class Window;
  class PlatformWindow;
  namespace ddgl
  {
    class RenderGL;
  }
}

class SceneManager;

class App
{
protected:
  static float deltaTime;
  static dudis::Window *window;
  static SceneManager *sceneManager;
  static double fixedDt;
  static std::shared_ptr<dudis::ddgl::DDRenderDevice> renderContext;

  static std::vector<std::function<void()>> _mainThreadQueue;
  static std::mutex _queueMutex;
  static dudis::PlatformWindow *_getPlatformWindow();

public:
  static std::function<void()> windowCallback;
  static void release();
  // static void setDeltaTime(float dt) {};
  static void setWindow(dudis::Window &nWindow);
  static void setSceneManager(SceneManager &nManager);
  static dudis::Window *getWindow();
  static SceneManager &getSceneManager() { return *sceneManager; }
  static void WindowDraw(const std::function<void()> &&nWindowCallback)
  {
    windowCallback = std::move(nWindowCallback);
  };

  static dudis::ddgl::DDRenderDevice *getRenderContext() { return renderContext.get(); };

  static void setRenderContext(std::shared_ptr<dudis::ddgl::DDRenderDevice> render);

  static void setFrameBufferId(int id, const char *label);
  static void runOnMainThread(std::function<void()> task);
  static void processMainThreadQueue();

  static float getFixedDt() { return fixedDt; }

  friend class dudis::ddgl::RenderGL;
};
