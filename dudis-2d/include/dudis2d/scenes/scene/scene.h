#pragma once

#include "dudis2d/core/component/physicsComponent/contactListenear/contactListenear.h"
#include "dudis2d/core/component/physicsComponent/debugDraw/debugDraw.h"
#include "dudis2d/core/entity/entity.h"
#include "dudis2d/core/utils/types.h"
#include "dudis2d/graphics/renderable.h"
#include <box2d/box2d.h>
#include <functional>
#include <memory>
#include <vector>

namespace dudis
{
  class RenderQueue;
}

class Scene : public dudis::Entity
{
private:
  std::function<void()> _release;
  std::function<void()> sceneEvents = nullptr;
  void _drawRenderableOrigin(dudis::Renderable *render);
  bool _start = false;
  void _initPropsInScene();

protected:
  dudis::SizeI size;
  Color clearColor;
  std::vector<std::shared_ptr<dudis::Renderable>> renderableList;
  std::unique_ptr<b2World> world;
  std::unique_ptr<dudis::DebugDraw> debugDraw;
  bool showPhysicsDebug = false;
  bool isSceneWithPhysic = false;

  dudis::ContactListner contactListner;

public:
  Scene();
  virtual ~Scene();
  static dudis::Scope<Scene> create();

  template <typename T>
  static std::unique_ptr<T> create();

  const char *label;

  virtual void start() override {};
  virtual void update() {};

  virtual void init() override;
  virtual void stop() { _start = false; }

  void addPhysics();
  void togglePhysicsDebug() { showPhysicsDebug = !showPhysicsDebug; }
  void setPhysicsDebug(const bool &enabled) { showPhysicsDebug = enabled; }

  void release()
  {
    if (_release)
    {
      _release();
      puts("extras da scene deletados");
    }
  }

  dudis::SizeI getSize();

  int getTotalRenderable() { return renderableList.size(); }

  void releaseAfterUse(std::function<void()> &&callback)
  {
    _release = std::move(callback);
  }

  void setSize(const dudis::SizeI &nSize);
  void setClearColor(Color nColor) { clearColor = nColor; };
  const Color &getClearColor() const { return clearColor; }
  void collectRenderCommands(dudis::RenderQueue *queque);

  void setEventListenear(std::function<void()> nCallback)
  {
    sceneEvents = nCallback;
  }

  // void drawAllChilren(dudis::Entity *render);

  b2World *getPhysicsWorld() { return this->world.get(); }
  std::function<void()> onSceneEvents() { return sceneEvents; }
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
