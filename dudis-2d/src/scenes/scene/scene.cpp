#include "dudis2d/scenes/scene/scene.h"
// #include "dudis2d/core/debug/dd-debug.h"
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

void Scene::_initPropsInScene()
{
}

Scene::~Scene()
{

  Log::Alert("[SCENE] Destruindo scene e liberando recursos");

  std::cout << "scene removida: " << label << "\n";

  this->release();

  renderableList.clear();
  Log::Success("[SCENE] Scene destruida com sucesso");
}
