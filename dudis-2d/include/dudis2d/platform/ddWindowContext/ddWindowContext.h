#pragma once

#include <memory>
#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/platform/platformWindow/platformWindow.h"
#include "dudis2d/platform/ddWindowContext/contextConfig.h"
// #include "dudis2d/platform/window/window.h"

namespace dudis
{
    class Window;

    // enum class Context
    // {
    //     Default,
    //     Personalized
    // };

    // enum class GfxAPI
    // {
    //     GL,
    //     RL,
    //     GL_ES,
    //     None
    // };

    class DDWindowContext
    {
    private:
        std::unique_ptr<PlatformWindow> _platform;
        std::unique_ptr<Window> _wInstance;

    public:
        void initWith(Context context = Context::Default, GfxAPI gfx = GfxAPI::None);
        Window &createWindow(const char *title, SizeI size);
        PlatformWindow *getPlatform() { return _platform.get(); }
    };
}
