#pragma once

#include <vector>
#include "dudis2d/core/utils/scope.h"

class Scene;

class SceneManager
{
protected:
  dudis::Scope<Scene> current;
  std::vector<dudis::Scope<Scene>> scenes;
  dudis::Scope<Scene> nextScene = nullptr;
  Scene *previousScene = nullptr;
  dudis::Scope<Scene> pendingScene = nullptr;
  bool _replaceMode = false;
  bool _pendingPop = false;
  bool _pendingPush = false;
  bool _remove = false;
  int _index = 0;
  bool loadScene;

public:
  bool replaceSceneMode = true;
  // Scene *getScene();
  bool setScene(dudis::Scope<Scene> nScene);
  Scene *getCurrentScene();
  std::vector<dudis::Scope<Scene>> getScenes();
  int getSceneIndex();
  size_t getTotalScenes();

  bool onRemove() { return _remove; }

  void pushScene(dudis::Scope<Scene> nScene);
  void applyChangeScene();
  void popScene();
  void dispose();
  void releaseCurrentScene();
};

// temp
#define PUSH_SCENE(scene) App::getSceneManager().pushScene(std::move(scene));
#define POP_SCENE() App::getSceneManager().popScene();
#define REPLACE_SCENE(scene) App::getSceneManager().setScene(std::move(scene));