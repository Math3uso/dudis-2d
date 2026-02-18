#pragma once

#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/core/utils/types.h"
#include "dudis2d/scenes/scene/scene.h"
#include "dudis2d/scenes/sceneManager/sceneManager.h"
#include "dudis2d/core/window/resolution.h"

class Window
{
protected:
  dudis::SizeI size;
  dudis::Vec2 pos;
  const char *title;
  Color clearColor = {32, 32, 32, 255};
  SceneManager *renderManager = nullptr;
  dudis::Resolution _resolution = dudis::Resolution({0, 0}, dudis::ResolutionPolicy::None);

public:
  Window(dudis::SizeI nSize, const char *nTitle);
  static Window *create(dudis::SizeI nSize, const char *nTitle)
  {
    _instance = std::make_unique<Window>(nSize, nTitle);
    return _instance.get();
  }

  void release();
  void Quit();
  void Running();
  bool init();
  void keepWindowCentered(bool isCenter) { this->_center = isCenter; }

  void SetFPS(const int nFPS) { SetTargetFPS(nFPS); }
  void SetClearColor(Color nColor) { clearColor = nColor; }
  void SetRenderManager(SceneManager &renderer);
  void setSize(const dudis::SizeI &nSize);
  void setResolution(dudis::Resolution &resolution) { _resolution = resolution; };

  const dudis::SizeI &getSize() const { return size; }
  const Color &getColor() const { return clearColor; }
  const dudis::Vec2 &getPos() const { return pos; }
  const dudis::Resolution &getResolution() const { return _resolution; }

private:
  bool _center = false;
  static std::unique_ptr<Window> _instance;

  const dudis::ResolutionProps _getResoltionProps();
  void _centerWindow();
};