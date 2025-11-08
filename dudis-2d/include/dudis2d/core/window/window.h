#pragma once

#include "dudis2d/core/ddCamera/ddCamera.h"
#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/core/utils/types.h"
#include "dudis2d/scenes/scene/scene.h"
#include "dudis2d/scenes/sceneManager/sceneManager.h"

namespace dudis {
enum class ResolutionPolicy {
  Letterbox, // Com bordas
  Crop,
  Stretch,
  None // default
};

class ResolutionProps {
public:
  Vec2 offset;
  float scale;
  ResolutionProps(Vec2 offset, float scale) : offset(offset), scale(scale) {}
};

class Resolution {
public:
  Size size;
  ResolutionPolicy _policy;
  Resolution(Size size, ResolutionPolicy type) : size(size), _policy(type) {}
};
} // namespace dudis

class Window {
protected:
  dudis::SizeI size;
  dudis::Vec2 pos;
  const char *title;
  Color clearColor = {0, 0, 0, 255};
  SceneManager *renderManager = nullptr;
  Camera2D camera;
  dudis::Resolution _resolution =
      dudis::Resolution({0, 0}, dudis::ResolutionPolicy::None);

public:
  dudis::DDCamera _globalCamera;

  Window(dudis::SizeI nSize, const char *nTitle);
  void Quit();
  void Running();
  void SetFPS(const int nFPS) { SetTargetFPS(nFPS); }
  void SetClearColor(Color nColor) { clearColor = nColor; }
  void SetRenderManager(SceneManager &renderer);
  void setSize(const dudis::Size &nSize);
  const dudis::SizeI &getSize() const { return size; }
  const Color &getColor() const { return clearColor; }
  const dudis::Vec2 &getPos() const { return pos; }
  const dudis::Resolution &getResolution() const { return _resolution; }

  void keepWindowCentered(bool isCenter) { this->_center = isCenter; }

  void setGlobalCamera(const dudis::DDCamera &&camera) {
    _globalCamera = std::move(camera);
  };

  void setGlobalCamera(const dudis::DDCamera &camera) {
    _globalCamera = camera;
  };

  const dudis::DDCamera &getGlobalCamera() const { return _globalCamera; }
  dudis::DDCamera &getGlobalCamera() { return _globalCamera; }

  // const dudis::Vec2 getResolutionOffset();
  void setResolution(dudis::Resolution &resolution) {
    _resolution = resolution;
  };

private:
  bool _center = false;
  // dudis::DDCamera _globalCamera;

  const dudis::ResolutionProps _getResoltionProps();
  void _centerWindow();

  void _drawTextureFromRenderManager(const RenderTexture2D &frameBuffer);
};