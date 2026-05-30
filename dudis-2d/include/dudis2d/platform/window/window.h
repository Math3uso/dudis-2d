#pragma once

#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/core/math/vec2.h"
#include "dudis2d/scenes/scene/scene.h"
#include "dudis2d/graphics/color.h"
#include "dudis2d/scenes/sceneManager/sceneManager.h"
// #include "dudis2d/platform/window/resolution.h"
#include "dudis2d/graphics/color.h"
#include "dudis2d/platform/platformWindow/platformWindow.h"
#include <queue>

namespace dudis
{

  namespace tests
  {
    class PlatformTestContext;
  }
  class PlatformWindow;

  class Window
  {
  protected:
    dudis::SizeI size;
    dudis::Vec2 pos;
    const char *title;
    dudis::Color clearColor = {32, 32, 32, 255};
    SceneManager *renderManager = nullptr;
    // dudis::Resolution _resolution = dudis::Resolution({0, 0}, dudis::ResolutionPolicy::None);
    std::queue<std::function<void()>> _closeCallback;
    void _close();
    PlatformWindow *_window;
    // PlatformWindow *_getPlatformWindow() { return _window; };

  public:
    Window(dudis::SizeI nSize, const char *nTitle);
    Window() = default;
    PlatformWindow *_getPlatformWindow() { return _window; };

    static Window *create(dudis::SizeI nSize, const char *nTitle)
    {
      _instance = std::make_unique<Window>(nSize, nTitle);
      return _instance.get();
    }

    void release();
    void Quit();
    void Running();

    void runByFrames(int frames);

    bool init();
    void keepWindowCentered(bool isCenter) { this->_center = isCenter; }
    bool isReady() const { return _window && _window->isReady(); }

    void SetFPS(const int nFPS) { _window->setFPSLimit(nFPS); }
    void SetClearColor(dudis::Color nColor) { clearColor = nColor; }
    void SetRenderManager(SceneManager &renderer);
    void setSize(const dudis::SizeI &nSize);
    // void setResolution(dudis::Resolution &resolution) { _resolution = resolution; };
    void setPlatformWindow(PlatformWindow *window);
    void onClose(const std::function<void()> callback) { _closeCallback.push(std::move(callback)); }

    const dudis::SizeI &
    getSize() const
    {
      return size;
    }
    const dudis::Color &getColor() const { return clearColor; }
    const dudis::Vec2 &getPos() const { return pos; }
    // const dudis::Resolution &getResolution() const { return _resolution; }

    void onQuit();

  private:
    bool _center = false;
    static std::unique_ptr<Window> _instance;

    // const dudis::ResolutionProps _getResoltionProps();
    void _centerWindow();

    // friend App;
    friend tests::PlatformTestContext;
  };

}