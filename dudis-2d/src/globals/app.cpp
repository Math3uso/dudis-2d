#include "dudis2d/globals/app.h"
#include "dudis2d/core/window/window.h"
#include "dudis2d/scenes/sceneManager/sceneManager.h"
#include <box2d/box2d.h>

float App::deltaTime = 0.f;
Window *App::window = nullptr;
SceneManager *App::sceneManager = nullptr;
std::function<void()> App::windowCallback = []() {};
std::function<void()> App::sceneCallback = []() {};
std::unordered_map<std::string, int> App::frameBuffers;
b2World *App::physicsWorld;
std::vector<b2Body *> App::bodies;
std::unordered_map<b2World *, std::vector<b2Body *>> App::worlds;
b2World *App::currentWorld = nullptr;

void App::setWindow(Window &nWindow) {
  window = &nWindow;

  return;
}

Window *App::getWindow() { return window; };

void App::setSceneManager(SceneManager &nManager) {
  sceneManager = &nManager;
  return;
}

void App::setFrameBufferId(int id, const char *label) {
  frameBuffers[std::string(label)] = id;
}

void App::setPhysicWorld(b2World *nWorld) {
  if (nWorld) {
    physicsWorld = nWorld;
  }
}

b2World *App::getPhysicsWorld() { return physicsWorld; }

void App::addPhysicsWorld(b2World *world) {
  if (world == nullptr) {
    return;
  }
  if (worlds.find(world) == worlds.end()) {
    worlds.emplace(world, std::vector<b2Body *>{});
    setCurrentPhysicsWorld(world);
    puts("PhysicsWorld adicionado [PHYSICS COMPONENT]");
  }
}

void App::setBody(b2World *world, b2Body *nBody) {
  auto it = worlds.find(world);

  if (it != worlds.end()) {
    it->second.push_back(nBody);
  }
}

// b2World *App::getB2World(b2World *world) {
//   auto it = worlds.find(world);
//   if (it != worlds.end()) {
//     return it->first;
//   }
//   return nullptr;
// }

void App::removePhysicsWorld(b2World *world) {
  if (!world) {
    return;
  }

  auto it = worlds.find(world);
  if (it != worlds.end()) {
    it->second.clear();
    worlds.erase(it);
  }
}