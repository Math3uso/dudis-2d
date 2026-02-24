#pragma once

#include "dudis2d/core/utils/types.h"
#include <functional>
#include <string>
#include <unordered_map>
class Window;

class SceneManager;

class App
{
protected:
  static float deltaTime;
  static Window *window;
  static SceneManager *sceneManager;
  static double fixedDt;

public:
  static std::function<void()> windowCallback;
  static std::function<void()> sceneCallback;
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

  static void SceneDraw(std::function<void()> nSceneCallback)
  {
    sceneCallback = nSceneCallback;
  }

  static void setFrameBufferId(int id, const char *label);

  static float getFixedDt() { return fixedDt; }
};
