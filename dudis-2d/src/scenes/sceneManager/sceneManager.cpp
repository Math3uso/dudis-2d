#include "dudis2d/scenes/sceneManager/sceneManager.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/scenes/scene/scene.h"
#include "string"

Scene *SceneManager::getScene() { return current.get(); }

bool SceneManager::setScene(dudis::Scope<Scene> nScene) {
  if (nScene.get()) {
    replaceSceneMode = false;
    nextScene = dudis::SetScope<Scene>(std::move(nScene));
    return true;
  }
  return false;
}

void SceneManager::popScene() {

  this->replaceSceneMode = true;

  if (!scenes.empty() && !current.get()) {
    if (index > 0) {
      index -= 1;
    } else {
      index = 0;
    }
    return;
    // scenes.pop_back();
  }

  // current.reset();
  return;
}

void SceneManager::pushScene(dudis::Scope<Scene> nScene) {

  dudis::Log::Info("================ Push Scene ================");

  if (nScene.get()) {
    scenes.push_back(std::move(nScene));

    dudis::Log::Info("nova scene add na lista");

    index = scenes.size() - 1;
    scenes[index]->start();
    auto sceneLabel = scenes[index]->label;

    dudis::Log::Success("Scene startada " + std::string(sceneLabel));
    dudis::Log::Info("================ Push Scene ================");
  }
}

void SceneManager::releaseCurrentScene() {

  dudis::Log::Info("================ releaseCurrentScene ================");

  if (current.get()->getFrameBuffer().id > 0) {
    UnloadRenderTexture(current.get()->getFrameBuffer());
  }

  dudis::Log::Success("Scene deletada -> " + std::string(current->label));

  current->release(); // esse release é da classe Scene e n do smart pointer.
  current.reset();

  dudis::Log::Info("================ releaseCurrentScene ================");
}

void SceneManager::dispose() {

  dudis::Log::Info("================ dispose scenes ================");

  dudis::Log::Alert("scenes sendo deletadas...");

  if (current && current.get()->getFrameBuffer().id > 0) {
    releaseCurrentScene();
  }

  if (!scenes.empty()) {
    for (const auto &scene : scenes) {
      if (scene.get()->getFrameBuffer().id > 0) {
        scene->release();
        UnloadRenderTexture(scene.get()->getFrameBuffer());
      }
    }

    scenes.clear();

    dudis::Log::Info("Lista de scenes removidas");
  }
  dudis::Log::Info("================ dispose scenes ================");

  return;
}

void SceneManager::applyChangeScene() {

  if (nextScene.get()) {
    dudis::Log::Info("Aplicando nova scene");
    if (current.get()) {
      releaseCurrentScene();
    }
    current = dudis::SetScope<Scene>(nextScene);
    current->start();
    nextScene.reset();
  }
}

int SceneManager::getSceneIndex() { return index; }

int SceneManager::getTotalScenes() { return scenes.size(); }

Scene *SceneManager::getCurrentScene() { return scenes[index].get(); };

// std::vector<dudis::Scope<Scene>> SceneManager::getScenes() { return scenes; }