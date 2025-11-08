#include "dudis2d/scenes/scene/scene.h"
// #include "dudis2d/core/debug/dd-debug.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/core/model/model.h"
#include "dudis2d/core/physicsComponent/debugDraw/debugDraw.h"
#include "dudis2d/core/window/window.h"
#include "dudis2d/globals/app.h"
#include "dudis2d/graphics/shape.h"
#include "dudis2d/graphics/ui/renderUI.h"
#include <algorithm>

using namespace std;
using namespace dudis;

Scene::Scene() {
  size = App::getWindow()->getSize();

  sceneTexure = LoadRenderTexture(size.w, size.h);

  clearColor = {32, 32, 32, 255};
}

Scene::~Scene() {

  if (sceneTexure.id > 0) {
    puts("frameBuffer deletado [SCENE]");
    UnloadRenderTexture(sceneTexure);
  }
}

const RenderTexture2D &Scene::getFrameBuffer() const { return sceneTexure; }

dudis::Scope<Scene> Scene::create() {
  auto nScene = std::make_unique<Scene>();
  return nScene;
}

// void Scene::addToRender(dudis::Scope<dudis::Renderable> render) {
//   renderableList.push_back(dudis::SetScope<dudis::Renderable>(render));
//   return;
// }

void Scene::addToRender(std::shared_ptr<dudis::Renderable> render) {

  if (!render) {
    dudis::Log::Error("Tried to add a null renderable to the scene.");
    return;
  }

  if (render->zIndex < 0) {
    render->zIndex++;
  }

  if (auto ui = dynamic_cast<dudis::RenderUI *>(render.get())) {
    ui->udpateLayout();
  }

  renderableList.push_back(render);

  Log::Info("total: " + to_string(renderableList.size()));

  return;
}

void Scene::render() {

  float deltaTime = GetFrameTime();

  if (isSceneWithPhysic) {

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world->Step(deltaTime, velocityIterations, positionIterations);
  }

  if (!models.empty()) {
    // for (const auto &model : models) {
    //   if (!model)
    //     return;

    //   model->update();
    //   model->render();
    // }
    for (size_t i = 0; i < models.size();) {
      auto &model = models[i];

      if (!model)
        return;

      if (model->getSceneProps().onDelete) {
        models.erase(models.begin());
        Log::Info("item deletado");
        i++;
        continue;
      }
      model->update();
      model->render();
      i++;
      // else {
      //   model->update();
      //   model->render();
      //   ++i;
      // }
    }
  }

  for (size_t i = 0; i < renderableList.size();) {

    const auto &render = renderableList[i];
    if (!render) {
      ++i;
      continue;
    }

    if (render->getSceneProps().onDelete) {
      renderableList.erase(renderableList.begin() + i);
      Log::Info("Renderable deletado");
      continue;
    }

    // render->update();
    //  render->runMotions();
    render->defaultUpdate();
    render->render();

    if (render->drawOrigin) {
      // auto origin = render->getOrigin();
      auto pos = render->getPos();

      if (auto shape = dynamic_cast<dudis::Renderable *>(render.get())) {
        auto color = shape->getColor();

        DrawRectangle(
            pos.x - 5, pos.y - 5, 10, 10,
            {(unsigned char)(255 - color.r), (unsigned char)(255 - color.g),
             (unsigned char)(255 - color.b), (unsigned char)(color.a)});

        continue;
      }

      DrawRectangle(pos.x - 5, pos.y - 5, 10, 10, RED);
      continue;
    }
    ++i;
  }

  if (isSceneWithPhysic && showPhysicsDebug && world) {
    world->DebugDraw();
  }
}

void Scene::addModel(shared_ptr<DDModel> nModel) {

  nModel->start();

  this->models.push_back(nModel);

  if (nModel->getAnimated()) {
    nModel->getAnimated()->drawToScene(this);
    dudis::Log::Alert("animation enviada");

    return;
  }

  dudis::Log::Alert("animation n enviada");

  // nModel->start();
  this->addToRender(nModel->getRenderable());

  // #ifdef DD_DEBUG
  //   DD_DebugDetails::registerScene(this);
  // #endif
}

void Scene::addPhysics() {
  this->isSceneWithPhysic = true;

  b2Vec2 gravity(0.0f, 9.8f);

  this->world = make_unique<b2World>(gravity);

  this->world->SetContactListener(&contactListner);

  this->debugDraw = std::make_unique<DebugDraw>();
  this->world->SetDebugDraw(debugDraw.get());

  App::setPhysicWorld(this->world.get());
}

void Scene::setSize(const SizeI &size) {
  UnloadRenderTexture(sceneTexure);
  sceneTexure = LoadRenderTexture(size.w, size.h);
}

void Scene::drawFrameBuffer(shared_ptr<FrameBuffer> frameBuffer) {
  frameBuffer->makeFrameBuffer();

  this->addToRender(frameBuffer);
}

void Scene::drawing(RenderTexture2D &frameBuffer, SizeI windowSize) {

  if (windowSize.w != size.w || windowSize.h != size.h) {
    size = {windowSize.w, windowSize.h};
    this->setSize(size);
  }

  frameBuffer = this->getFrameBuffer();

  BeginTextureMode(frameBuffer);
  ClearBackground(this->getClearColor());

  if (App::sceneCallback) {
    App::sceneCallback();
  }

  this->render();
  this->update();

  EndTextureMode();
}