#pragma once

#include "dudis2d/core/model/model.h"
#include "dudis2d/core/physicsComponent/contactListenear/contactListenear.h"
#include "dudis2d/core/physicsComponent/debugDraw/debugDraw.h"
#include "dudis2d/core/utils/types.h"
#include "dudis2d/graphics/frameBuffer/frameBuffer.h"
#include "dudis2d/graphics/renderable.h"
#include <box2d/box2d.h>
#include <functional>
#include <memory>
#include <vector>

class Scene {
private:
  std::function<void()> _release;
  std::function<void()> sceneEvents = nullptr;

protected:
  RenderTexture2D sceneTexure = {};
  dudis::SizeI size;
  Color clearColor;
  std::vector<std::shared_ptr<dudis::Renderable>> renderableList;
  std::unique_ptr<b2World> world;
  std::unique_ptr<dudis::DebugDraw> debugDraw;
  bool showPhysicsDebug = false;
  bool isSceneWithPhysic = false;
  std::vector<std::shared_ptr<dudis::DDModel>> models;
  dudis::ContactListner contactListner;

public:
  Scene();
  virtual ~Scene();
  static dudis::Scope<Scene> create();
  const char *label;
  // virtual void start() = 0;
  // virtual void update() = 0;
  virtual void start() {};
  virtual void update() {};

  void addPhysics();
  void togglePhysicsDebug() { showPhysicsDebug = !showPhysicsDebug; }
  void setPhysicsDebug(bool enabled) { showPhysicsDebug = enabled; }

  void release() {
    if (_release) {
      _release();
      puts("extras da scene deletados");
    }
  }

  dudis::SizeI getSize();

  int getTotalRenderable() { return renderableList.size(); }

  void releaseAfterUse(std::function<void()> callback) { _release = callback; }
  void render();
  void setSize(dudis::SizeI nSize);
  void setClearColor(Color nColor) { clearColor = nColor; };
  RenderTexture2D &getFrameBuffer();
  Color getClearColor() { return clearColor; }

  void addToRender(std::shared_ptr<dudis::Renderable> renderable);
  void addModel(std::shared_ptr<dudis::DDModel> nModel);
  void drawFrameBuffer(std::shared_ptr<dudis::FrameBuffer> frameBuffer);
  void drawing(RenderTexture2D &frameBuffer, dudis::SizeI windowSize);

  void setEventListenear(std::function<void()> nCallback) {
    sceneEvents = nCallback;
  }

  b2World *getPhysicsWorld() { return this->world.get(); }
  std::function<void()> onSceneEvents() { return sceneEvents; }
};

#define CREATE_SCENE(Scene)                                                    \
  static dudis::Scope<Scene> create() {                                        \
    auto nScene = std::make_unique<Scene>();                                   \
    return nScene;                                                             \
  }
