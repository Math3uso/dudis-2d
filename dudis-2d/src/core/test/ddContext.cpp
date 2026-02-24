#include "dudis2d/core/test/ddContext.h"

using namespace dudis;
using namespace test;

Window DDContext::window;
SceneManager DDContext::manager;

void DDContext::InitContext()
{
    window = Window(SizeI(800, 600), "Janela");

    window.init();

    App::setSceneManager(manager);

    window.SetRenderManager(manager);
}