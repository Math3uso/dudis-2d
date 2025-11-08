#include "scenes/scene-reso/scene-reso.h"
#include "raygui.h"

DD_NAMESPACE;

DD_RENDER;

void SetResolution(Window *window, Resolution *reso) {
  App::getWindow()->setResolution(*reso);
  App::getWindow()->setSize({reso->size.w, reso->size.h});
}

void SceneReso::start() {

  this->label = "reso";

  auto dflt = new Resolution({800, 600}, ResolutionPolicy::Letterbox);
  auto hd = new Resolution({1280, 720}, ResolutionPolicy::Letterbox);
  auto fullHd = new Resolution({1920, 1080}, ResolutionPolicy::Letterbox);

  auto bloco = DDRectangle::create({100, 100}, {0, 0});

  App::SceneDraw([hd, dflt, fullHd]() {
    Window *window = App::getWindow();

    if (GuiButton({100, 100, 100, 40}, "padrão")) {
      SetResolution(window, dflt);
    }

    if (GuiButton({100, 150, 100, 40}, "HD")) {
      SetResolution(window, hd);
    }

    if (GuiButton({100, 200, 100, 40}, "Full HD")) {
      SetResolution(window, fullHd);
    }
  });

  this->releaseAfterUse([dflt, hd, fullHd]() {
    delete dflt;
    delete hd;
    delete fullHd;
  });

  this->addToRender(bloco);
}

void SceneReso::update() {}