#include "dudis2d/scenes/scene/scene.h"
// #include "dudis2d/core/debug/dd-debug.h"
#include "dudis2d/core/component/physicsComponent/debugDraw/debugDraw.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/core/model/model.h"
#include "dudis2d/core/window/window.h"
#include "dudis2d/globals/app.h"
#include "dudis2d/graphics/renderQueue/renderQueue.h"
#include <algorithm>

using namespace std;
using namespace dudis;

Scene::Scene()
{

  // this->init();

  size = App::getWindow()->getSize();

  clearColor = {32, 32, 32, 255};
}

void Scene::init()
{

  _start = true;

  std::cout << "Inicializando scene: " << "\n";
  std::cout << this->renderableList.size() << "\n";

  if (world && App::getCurrentWolrd() != world.get())
  {
    App::setCurrentPhysicsWorld(world.get());
  }
}

dudis::Scope<Scene> Scene::create()
{
  auto nScene = std::make_unique<Scene>();
  return nScene;
}

void Scene::collectRenderCommands(RenderQueue *queue)
{
  this->_initPropsInScene();

  this->update();

  for (auto &entity : _children)
  {
    if (!entity)
      continue;

    entity->defaultUpdate();
    entity->buildRenderCommands(queue);
  }
}

void Scene::setSize(const SizeI &size) {}

void Scene::addPhysics()
{
  this->isSceneWithPhysic = true;

  b2Vec2 gravity(0.0f, 9.8f);

  this->world = make_unique<b2World>(gravity);

  this->world->SetContactListener(&contactListner);

  this->debugDraw = std::make_unique<DebugDraw>();
  this->world->SetDebugDraw(debugDraw.get());

  App::addPhysicsWorld(this->world.get());

  // App::setPhysicWorld(this->world.get());
}

void Scene::_initPropsInScene()
{
  float deltaTime = GetFrameTime();

  // float deltaTime = App::getFixedDt();

  if (isSceneWithPhysic)
  {

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    world->Step(deltaTime, velocityIterations, positionIterations);
  }

  if (isSceneWithPhysic && showPhysicsDebug && world)
  {
    world->DebugDraw();
  }
}

Scene::~Scene()
{

  Log::Alert("[SCENE] Destruindo scene e liberando recursos");

  std::cout << "scene removida: " << label << "\n";

  this->release();

  if (world)
  {
    Log::Alert("====================physicsComponent====================");
    Log::Info(
        "\n\u2003\u2003[PHYSICS COMPONENT] Removendo PhysicsWorld da scene");
    for (b2Body *body = world->GetBodyList(); body;)
    {
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

  renderableList.clear();
  Log::Success("[SCENE] Scene destruida com sucesso");
}
