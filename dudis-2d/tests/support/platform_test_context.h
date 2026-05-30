#pragma once

#include <memory>

#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/graphics/ddgl/render/renderGL.h"
#include "dudis2d/platform/ddWindowContext/ddWindowContext.h"
#include "dudis2d/platform/platformWindow/platformWindow.h"
#include "dudis2d/platform/window/window.h"

namespace dudis::tests
{

    class PlatformTestContext
    {
    public:
        bool initOpenGLWindow(const char *title = "dudis platform test",
                              SizeI size = SizeI(320, 240));
        void shutdown();

        // Window &windowRef() const { return *window; }
        ddgl::DDRenderDevice *renderRef() const { return render.get(); }
        PlatformWindow *platformWindowRef() { return context.getPlatform(); }

    private:
        DDWindowContext context;
        Window *window = nullptr;
        std::shared_ptr<ddgl::DDRenderDevice> render;
    };
}
