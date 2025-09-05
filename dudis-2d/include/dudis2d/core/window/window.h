#pragma once

#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/core/utils/types.h"
#include "dudis2d/scenes/scene/scene.h"
#include "dudis2d/scenes/sceneManager/sceneManager.h"

class Window
{
protected:
  dudis::SizeI size;
  dudis::Vec2 pos;
  const char *title;
  Color clearColor = {0, 0, 0, 255};
  SceneManager *renderManager = nullptr;
  Camera2D camera;

public:
  Window(dudis::SizeI nSize, const char *nTitle);
  void Quit();
  void Running();
  void SetFPS(int nFPS) {
    SetTargetFPS(nFPS);
  }
  void SetClearColor(Color nColor) {
    clearColor = nColor;
  }
  void SetRenderManager(SceneManager &renderer);
  dudis::SizeI getSize() {
    return size;
  }
  Color getColor() {
    return clearColor;
  }
  dudis::Vec2 getPos() {
    return pos;
  }
};