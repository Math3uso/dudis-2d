#include "dudis2d/scenes/scene/scene.h"
// #include "dudis2d/core/debug/dd-debug.h"
#include "dudis2d/core/component/physicsComponent/debugDraw/debugDraw.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/core/model/model.h"
#include "dudis2d/core/window/window.h"
#include "dudis2d/globals/app.h"
#include "dudis2d/graphics/shape.h"
#include "dudis2d/graphics/ui/renderUI.h"
#include <algorithm>

using namespace std;
using namespace dudis;

Scene::Scene() {

  // cout << "iniciando construtor scene" << "\n";

  // this->init();

  size = App::getWindow()->getSize();

  sceneTexure = LoadRenderTexture(size.w, size.h);

  clearColor = {32, 32, 32, 255};
}

void Scene::init() {

  _start = true;

  std::cout << "Inicializando scene: " << "\n";
  std::cout << this->renderableList.size() << "\n";

  if (world && App::getCurrentWolrd() != world.get()) {
    App::setCurrentPhysicsWorld(world.get());
  }
}

Scene::~Scene() {

  Log::Alert("[SCENE] Destruindo scene e liberando recursos");

  if (sceneTexure.id > 0) {
    puts("frameBuffer deletado [SCENE]");
    std::cout << "scene removida: " << label << "\n";
    UnloadRenderTexture(sceneTexure);

    this->release();

    if (world) {
      Log::Alert("====================physicsComponent====================");
      Log::Info(
          "\n\u2003\u2003[PHYSICS COMPONENT] Removendo PhysicsWorld da scene");
      for (b2Body *body = world->GetBodyList(); body;) {
        b2Body *next = body->GetNext();
        world->DestroyBody(body);
        body = next;
        puts("\u2003\u2003body deletado");
      }
      // Remover do map global
      App::removePhysicsWorld(world.get());
      Log::Info(
          "\n\u2003\u2003[PHYSICS COMPONENT] PhysicsWorld removido de scene\n");
    }
    Log::Alert("====================physicsComponent====================\n");
  }
  renderableList.clear();
  Log::Success("[SCENE] Scene destruida com sucesso");
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

  // [ADDMODEL]=========================================================================
  // if (!models.empty()) {
  //   for (size_t i = 0; i < models.size();) {
  //     auto &model = models[i];

  //     if (!model)
  //       return;

  //     if (model->getSceneProps().onDelete) {
  //       models.erase(models.begin());
  //       Log::Info("item deletado");
  //       i++;
  //       continue;
  //     }
  //     model->update();
  //     model->render();
  //     i++;
  //   }
  // }
  // [ADDMODEL]=========================================================================

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
    this->drawAllChilren(render.get());

    // for (const auto &child : render->getChildren()) {
    //   if (Renderable *childRender = dynamic_cast<Renderable *>(child.get()))
    //   {
    //     childRender->render();
    //   }
    //   // child->render();
    // }

    _drawRenderableOrigin(render.get());
    ++i;
  }

  if (isSceneWithPhysic && showPhysicsDebug && world) {
    world->DebugDraw();
  }
}

void Scene::draw() {

  this->_initPropsInScene();

  for (auto &entity : _children) {
    if (!entity)
      continue;

    // entity->_sortChildrenByIndex();
    entity->defaultUpdate();
    entity->render();
    this->drawAllChilren(entity.get());
    //_drawRenderableOrigin(entity.get());
  }
}

// [ADDMODEL]=========================================================================
// void Scene::addModel(shared_ptr<DDModel> nModel) {

//   nModel->start();

//   this->models.push_back(nModel);

//   if (nModel->getAnimated()) {
//     nModel->getAnimated()->drawToScene(this);
//     dudis::Log::Alert("animation enviada");

//     return;
//   }

//   dudis::Log::Alert("animation n enviada");

//   // nModel->start();
//   this->addToRender(nModel->getRenderable());

//   // #ifdef DD_DEBUG
//   //   DD_DebugDetails::registerScene(this);
//   // #endif
// }

// [ADDMODEL]=========================================================================

void Scene::setSize(const SizeI &size) {
  UnloadRenderTexture(sceneTexure);
  sceneTexure = LoadRenderTexture(size.w, size.h);
}

void Scene::drawFrameBuffer(shared_ptr<FrameBuffer> frameBuffer) {
  frameBuffer->makeFrameBuffer();

  this->addToRender(frameBuffer);
}

// RenderTexture2D Scene::getFrameBufferWithScene(SizeI windowSize) {

//   auto &camera = App::getWindow()->getGlobalCamera();

//   if (windowSize.w != size.w || windowSize.h != size.h) {
//     size = {windowSize.w, windowSize.h};
//     this->setSize(size);
//   }

//   auto frameBuffer = this->getFrameBuffer();

//   BeginTextureMode(frameBuffer);
//   ClearBackground(this->getClearColor());

//   if (App::sceneCallback) {
//     App::sceneCallback();
//   }

//   BeginMode2D(camera.getCameraProps());

//   // DrawCircle(0, 0, 20, RED);
//   this->render();
//   this->update();

//   EndMode2D();

//   EndTextureMode();

//   return frameBuffer;
// }

void Scene::drawing(RenderTexture2D &frameBuffer, SizeI windowSize) {

  auto &camera = App::getWindow()->getGlobalCamera();

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

  BeginMode2D(camera.getCameraProps());

  // DrawCircle(0, 0, 20, RED);
  this->render();
  this->update();

  EndMode2D();

  EndTextureMode();
}

void Scene::_drawRenderableOrigin(Renderable *render) {
  if (render->drawOrigin) {
    // auto origin = render->getOrigin();
    auto pos = render->getPos();

    if (auto shape = dynamic_cast<dudis::Renderable *>(render)) {
      auto color = shape->getColor();

      DrawRectangle(pos.x - 5, pos.y - 5, 10, 10,
                    {(unsigned char)(255 - color.r),
                     (unsigned char)(255 - color.g),
                     (unsigned char)(255 - color.b), (unsigned char)(color.a)});

      return;
    }

    DrawRectangle(pos.x - 5, pos.y - 5, 10, 10, RED);
    return;
  }
}

void Scene::drawAllChilren(Entity *render) {
  if (render->getChildren().size() == 0) {
    return;
  }

  for (const auto &child : render->getChildren()) {
    // child->getGlobalMatrix();
    child->render();
    child->defaultUpdate();
    // _drawRenderableOrigin(render);
    this->drawAllChilren(child.get());
  }
}

void Scene::addPhysics() {
  this->isSceneWithPhysic = true;

  b2Vec2 gravity(0.0f, 9.8f);

  this->world = make_unique<b2World>(gravity);

  this->world->SetContactListener(&contactListner);

  this->debugDraw = std::make_unique<DebugDraw>();
  this->world->SetDebugDraw(debugDraw.get());

  App::addPhysicsWorld(this->world.get());

  // App::setPhysicWorld(this->world.get());
}

void Scene::_initPropsInScene() {
  float deltaTime = GetFrameTime();

  if (isSceneWithPhysic) {

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world->Step(deltaTime, velocityIterations, positionIterations);
  }

  if (isSceneWithPhysic && showPhysicsDebug && world) {
    world->DebugDraw();
  }
}