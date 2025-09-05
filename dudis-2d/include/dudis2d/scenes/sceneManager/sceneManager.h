#pragma once

#include "dudis2d/core/utils/types.h"
#include <vector>

class Scene;

class SceneManager {
protected:
  dudis::Scope<Scene> current;
  std::vector<dudis::Scope<Scene>> scenes;
  dudis::Scope<Scene> nextScene = nullptr;
  int index;
  bool loadScene;

public:
  bool replaceSceneMode = true;
  Scene *getScene();
  bool setScene(dudis::Scope<Scene> nScene);
  Scene *getCurrentScene();
  std::vector<dudis::Scope<Scene>> getScenes();
  int getSceneIndex();
  int getTotalScenes();
  void pushScene(dudis::Scope<Scene> nScene);
  void applyChangeScene();
  void popScene();
  void dispose();
  void releaseCurrentScene();
};