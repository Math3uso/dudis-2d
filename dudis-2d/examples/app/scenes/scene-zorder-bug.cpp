#include "scenes/scene-zorder-bug.h"

using namespace dudis;

bool SceneZOrderBug::start()
{
  label = "scene-zorder-bug";

  setClearColor(dudis::Color(25, 25, 25, 255));

  parentRect = DDRectangle::create(Size(260, 260), Vec2(120, 120));
  parentRect->setColor(dudis::Color(180, 180, 180, 255));
  this->addChild(parentRect, 10);

  oldBlueChild = DDRectangle::create(Size(200, 200), Vec2(30, 30));
  oldBlueChild->setColor(dudis::Color(0, 121, 241, 210));
  parentRect->addChild(oldBlueChild, 50);

  std::cout << "\n[BUG DEMO] Fase 1\n";
  std::cout << "parent z (inicial): " << parentRect->getZOrder() << "\n";
  std::cout << "blue child z (local 50): " << oldBlueChild->getZOrder() << "\n";
  std::cout << "Esperado ate aqui: OK\n";
  return true;
}

void SceneZOrderBug::update()
{
  frameCount++;

  if (!step2Done && frameCount > 120)
  {
    parentRect->setZOrder(200);

    newRedChild = DDRectangle::create(Size(200, 200), Vec2(30, 30));
    newRedChild->setColor(dudis::Color(230, 41, 55, 210));
    parentRect->addChild(newRedChild, 40);

        std::cout << "\n[BUG DEMO] Fase 2\n";
    std::cout << "parent z (apos setZOrder 200): " << parentRect->getZOrder() << "\n";
    std::cout << "blue child z antigo (local 50, deveria acompanhar pai): "
              << oldBlueChild->getZOrder() << "\n";
    std::cout << "red child z novo (local 40, adicionado apos mover pai): "
              << newRedChild->getZOrder() << "\n";
    std::cout << "Esperado por z local: BLUE(50) acima de RED(40)\n";
    std::cout << "Resultado real: RED desenha por cima (z absoluto inconsistente)\n";

    step2Done = true;
  }
}
