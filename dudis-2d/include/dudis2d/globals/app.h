#pragma once

// #include "dudis2d/core/utils/types.h"
#include <functional>
#include <string>
#include <unordered_map>
#include <queue>
#include <mutex>

class Window;

class SceneManager;

class App
{
protected:
  static float deltaTime;
  static Window *window;
  static SceneManager *sceneManager;
  static double fixedDt;

  static std::vector<std::function<void()>> _mainThreadQueue;
  static std::mutex _queueMutex;

public:
  static std::function<void()> windowCallback;
  static void release();
  // static void setDeltaTime(float dt) {};
  static void setWindow(Window &nWindow);
  static void setSceneManager(SceneManager &nManager);
  static Window *getWindow();
  static SceneManager &getSceneManager() { return *sceneManager; }
  static void WindowDraw(const std::function<void()> &&nWindowCallback)
  {
    windowCallback = std::move(nWindowCallback);
  };

  static void setFrameBufferId(int id, const char *label);
  static void runOnMainThread(std::function<void()> task);
  static void processMainThreadQueue();

  static float getFixedDt() { return fixedDt; }
};
