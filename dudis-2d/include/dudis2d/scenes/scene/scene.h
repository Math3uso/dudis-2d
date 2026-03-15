#pragma once

#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/utils/types.h"
#include "dudis2d/graphics/renderable.h"
#include <functional>
#include <memory>
#include <vector>
#include "dudis2d/graphics/ddAssets/texture2D.h"

namespace dudis
{
  class RenderQueue;
}

class Scene : public dudis::Entity
{
private:
  std::function<void()> _release;
  std::function<void()> sceneEvents = nullptr;
  bool _start = false;
  bool _paused = false;
  void _initPropsInScene();
  dudis::res::Texture2DManager _resManager;

protected:
  dudis::SizeI size;
  dudis::Color clearColor;
  // Physics integration temporarily disconnected (components remain available).

public:
  Scene();
  virtual ~Scene();
  static dudis::Scope<Scene> create();

  template <typename T>
  static std::unique_ptr<T> create();

  const char *label;

  dudis::SizeI getSize() {};
  const dudis::res::Texture2DManager &getTexture2DManager() const { return _resManager; }
  dudis::res::Texture2DManager &getTexture2DManager() { return _resManager; }
  const dudis::Color &getClearColor() const { return clearColor; }

  void setSize(const dudis::SizeI &nSize);
  void setClearColor(dudis::Color nColor) { clearColor = nColor; };

  virtual void start() override {};
  virtual void update() {};
  virtual void exit() {};
  virtual void init() override;
  virtual void stop() { _start = false; }
  virtual void onPause() {};
  virtual void onReume() {};
  virtual void addChild(std::shared_ptr<Entity> child) override;
  virtual void addChild(std::shared_ptr<Entity> child, const int zOrder) override;

  void releaseAfterUse(std::function<void()> &&callback) { _release = std::move(callback); }

  void collectRenderCommands(dudis::RenderQueue *queque);

  void setEventListenear(std::function<void()> nCallback) { sceneEvents = nCallback; }

  std::function<void()> onSceneEvents() { return sceneEvents; }

  void pause()
  {
    onPause();
    _paused = true;
  };
  void resume()
  {
    onReume();
    _paused = false;
  };

  void release()
  {
    if (_release)
    {
      _release();
      puts("extras da scene deletados");
    }
  }
};

template <typename T>
std::unique_ptr<T> Scene::create()
{
  return std::make_unique<T>();
}

#define CREATE_SCENE(Scene)                  \
  static dudis::Scope<Scene> create()        \
  {                                          \
    auto nScene = std::make_unique<Scene>(); \
    return nScene;                           \
  }
