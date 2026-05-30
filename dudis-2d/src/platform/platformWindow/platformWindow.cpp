#include "dudis2d/platform/platformWindow/platformWindow.h"
#include "dudis2d/platform/platformWindow/SDLContext.h"

using namespace std;
using namespace dudis;

unique_ptr<PlatformWindow> PlatformWindow::_create()
{
    return make_unique<SDLContext>(GfxAPI::GL);
}