#include "dudis2d/platform/ddWindowContext/ddWindowContext.h"
#include "dudis2d/platform/platformWindow/RLContext.h"
#include "dudis2d/platform/platformWindow/SDLContext.h"
#include "dudis2d/platform/window/window.h"

using namespace std;
using namespace dudis;

void DDWindowContext::initWith(Context context, GfxAPI gfx)
{
    switch (context)
    {
    case Context::Default:
        _platform = make_unique<RLContext>();

        break;
    case Context::Personalized:
        // _platform = make_unique
        _platform = make_unique<SDLContext>(gfx);
        break;
    }
}

Window &DDWindowContext::createWindow(const char *title, SizeI size)
{

    assert(_platform && "DDWindowContext::initWith precisa ser chamado antes de createWindow");

    _platform->setSize(size);
    _platform->setTitle(title);

    //_platform->init();
    _wInstance = make_unique<Window>(size, title);
    _wInstance->setPlatformWindow(_platform.get());

    return *_wInstance;
}