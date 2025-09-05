#pragma once

#include <functional>
#include <string>
#include <unordered_map>

class Window;

class SceneManager;

class b2World;

class App {
protected:
  static float deltaTime;
  static Window *window;
  static SceneManager *sceneManager;
  static std::unordered_map<std::string, int> frameBuffers;
  static b2World *physicsWorld;

public:
  static std::function<void()> windowCallback;
  static std::function<void()> sceneCallback;
  // static void setDeltaTime(float dt) {};
  static void setWindow(Window &nWindow);
  static void setSceneManager(SceneManager &nManager);
  static Window *getWindow();
  static SceneManager &getSceneManager() { return *sceneManager; }
  static void WindowDraw(std::function<void()> nWindowCallback) {
    windowCallback = nWindowCallback;
  };

  static void SceneDraw(std::function<void()> nSceneCallback) {
    sceneCallback = nSceneCallback;
  }

  static void setPhysicWorld(b2World *nworld);
  static b2World *getPhysicsWorld();

  static void setFrameBufferId(int id, const char *label);
};