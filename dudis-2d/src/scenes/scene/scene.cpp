#include "dudis2d/scenes/scene/scene.h"
// #include "dudis2d/core/debug/dd-debug.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/core/model/model.h"
#include "dudis2d/platform/window/window.h"
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
}

dudis::Scope<Scene> Scene::create()
{
  auto nScene = std::make_unique<Scene>();
  return nScene;
}

void Scene::collectRenderCommands(RenderQueue *queue)
{
  this->_initPropsInScene();

  if (_paused)
    return;

  this->update();
  this->updateTree();
  this->_sortChildrenByIndex();

  for (auto &entity : _children)
  {
    if (!entity || _paused)
      continue;

    if (entity->_ready)
    {
      // entity->_sortChildrenByIndex();
      // entity->defaultUpdate();
      entity->buildRenderCommands(queue);
    }
  }
}

void Scene::addChild(std::shared_ptr<Entity> child)
{
  child->_setRootEntity(this);
  Entity::addChild(child);
}

void Scene::addChild(std::shared_ptr<Entity> child, const int zOrder)
{
  child->_zOrder = zOrder;
  this->addChild(child);
}

void Scene::setSize(const SizeI &size)
{
}

void Scene::_initPropsInScene()
{
}

Scene::~Scene()
{

  Log::Alert("[SCENE] Destruindo scene e liberando recursos");

  std::cout << "scene removida: " << label << "\n";

  _children.clear();
  this->release();

  // liberando texturas
  //_resManager.unloadAll();

  Log::Success("[SCENE] Scene destruida com sucesso");
}
