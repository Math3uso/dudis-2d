#include "dudis2d/graphics/ui/UIRoot/UIRoot.h"
#include "dudis2d/core/window/window.h"

using namespace dudis;
using namespace std;

void UIRoot::createLayout() {

  ui = LoadRenderTexture(800, 600);
  paddingGlobal = 0.f;

  std::cout << "total de childrens: " << children.size() << "\n";

  BeginTextureMode(ui);
  // ClearBackground(BLANK);
  // Limpa a textura com TRANSPARENTE
  ClearBackground(BLANK); // RAYLIB define BLANK como {0,0,0,0}

  // Desenhe um retângulo de fundo só pra referência
  DrawRectangle(0, 0, ui.texture.width, ui.texture.height, Fade(RED, 0.2f));

  for (const auto &child : children) {
    child->render();
    child->udpateLayout();
  }

  EndTextureMode();
}

void UIRoot::render() {
  Rectangle size = {0, 0, (float)ui.texture.width, -(float)ui.texture.height};

  DrawTextureRec(ui.texture, size, {0, 0}, WHITE);
}

shared_ptr<UIRoot> UIRoot::create() {
  auto root = make_shared<UIRoot>();
  return root;
}