#include "dudis2d/scenes/sceneManager/sceneManager.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/scenes/scene/scene.h"
#include "dudis2d/core/utils/types.h"
#include "string"

// Scene *SceneManager::getScene() { return current.get(); }

bool SceneManager::setScene(dudis::Scope<Scene> nScene)
{
  _replaceMode = true;
  nextScene = std::move(nScene);
  return true;
}

void SceneManager::popScene()
{

  if (!scenes.empty())
  {
    _pendingPop = true;
    if (_index > 0)
    {
      _index -= 1;
    }
    else
    {
      _index = 0;
    }
  }
  std::cout << _index << "\n";

  std::cout << "scene atual q dveria ser desenhada << "
            << this->getCurrentScene()->label << "\n";
}

void SceneManager::pushScene(dudis::Scope<Scene> nScene)
{

  dudis::Log::Info("================ Push Scene ================");

  dudis::Log::Info("preparando Scene para add na lista");

  if (nScene)
  {
    scenes.push_back(std::move(nScene));
    _index = scenes.size() - 1;
    _pendingPush = true;
  }

  dudis::Log::Info("================ Push Scene ================");
}

void SceneManager::releaseCurrentScene() {}

void SceneManager::applyChangeScene()
{
  if (scenes.empty() && !_replaceMode)
    return;

  if (_pendingPush)
  {
    scenes.back()->start();
    scenes.back()->init();
    _pendingPush = false;
  }
  else if (_pendingPop)
  {
    scenes.pop_back();
    scenes.back()->init();
    // scenes.back()->start();
    _pendingPop = false;
  }
  else if (_replaceMode)
  {
    if (scenes.empty())
    {
      scenes.push_back(std::move(nextScene));
    }
    else
    {
      scenes[_index] = std::move(nextScene);
    }
    scenes[_index]->start();
    scenes[_index]->init();
    nextScene.reset();
    nextScene = nullptr;
    _replaceMode = false;
  }
}

int SceneManager::getSceneIndex() { return _index; }

size_t SceneManager::getTotalScenes() { return scenes.size(); }

Scene *SceneManager::getCurrentScene() { return scenes[_index].get(); };

void SceneManager::dispose()
{

  dudis::Log::Info("================ dispose scenes ================\n");

  dudis::Log::Alert("scenes sendo deletadas...");

  if (current)
  {
    releaseCurrentScene();
  }

  if (!scenes.empty())
  {

    scenes.clear();

    dudis::Log::Info("Lista de scenes removidas");
  }
  dudis::Log::Info("================ dispose scenes ================\n");

  return;
}