#include "dudis2d/core/test/ddContext.h"

using namespace dudis;
using namespace test;

void DDContext::InitContext()
{
    manager = std::make_unique<SceneManager>();
    window = std::make_unique<Window>(SizeI(800, 600), "Janela");

    window->init();

    App::setSceneManager(*manager.get());

    window->SetRenderManager(*manager.get());
}

void DDContext::ExitContext()
{

    window->Quit();
    window->release();

    window.reset();
    manager.reset();
}

void DDContext::pushDraw(std::shared_ptr<dudis::Renderable> renderable)
{
    manager->getCurrentScene()->addChild(renderable);
}