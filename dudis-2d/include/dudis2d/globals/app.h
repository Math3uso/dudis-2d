#pragma once

#include "dudis2d/core/utils/types.h"
#include <functional>
#include <string>
#include <unordered_map>
class Window;

class SceneManager;

class b2World;

class b2Body;

class App {
protected:
  static float deltaTime;
  static Window *window;
  static SceneManager *sceneManager;
  static std::unordered_map<std::string, int> frameBuffers;
  static b2World *physicsWorld;
  static std::vector<b2Body *> bodies;
  static std::unordered_map<b2World *, std::vector<b2Body *>> worlds;
  static b2World *currentWorld;

public:
  static std::function<void()> windowCallback;
  static std::function<void()> sceneCallback;
  // static void setDeltaTime(float dt) {};
  static void setWindow(Window &nWindow);
  static void setSceneManager(SceneManager &nManager);
  static Window *getWindow();
  static SceneManager &getSceneManager() { return *sceneManager; }
  static void WindowDraw(const std::function<void()> &&nWindowCallback) {
    windowCallback = std::move(nWindowCallback);
  };

  static void SceneDraw(std::function<void()> nSceneCallback) {
    sceneCallback = nSceneCallback;
  }

  static void setPhysicWorld(b2World *nworld);
  static b2World *getPhysicsWorld();

  static void setFrameBufferId(int id, const char *label);

  static void setBody(b2World *world, b2Body *nBody);

  static void addPhysicsWorld(b2World *world);

  // static b2World *getB2World(b2World *world);

  static void setCurrentPhysicsWorld(b2World *world) { currentWorld = world; }
  static b2World *getCurrentWolrd() { return currentWorld; }

  static void removePhysicsWorld(b2World *world);
};