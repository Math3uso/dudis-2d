#include "scenes/scene-layout/sceneLayout.h"
#include "dudis2d/graphics.h"

using namespace dudis;

void SceneLayout::start() {
  label = "scene layout";

  auto root = UIRoot::create();

  auto bloco = Container::create(Layout::Colunm);
  bloco->paddingGlobal = 10.f;
  bloco->setBackgroundColor(RED);
  bloco->setSize({400, 500});

  auto child1 = Container::create();
  child1->setBackgroundColor(BLUE);
  child1->setSize({100, 100});

  auto child2 = Container::create();
  child2->setBackgroundColor(GREEN);
  child2->setSize({100, 100});

  bloco->addChildren(child1);
  bloco->addChildren(child2);
  bloco->addChildren(child1);

  root->addChildren(bloco);

  root->createLayout();

  this->addToRender(root);
}

void SceneLayout::update() {}