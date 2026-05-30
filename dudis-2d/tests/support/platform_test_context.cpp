#include "support/platform_test_context.h"

#include "dudis2d/globals/app.h"

namespace dudis::tests
{
    bool PlatformTestContext::initOpenGLWindow(const char *title, SizeI size)
    {
        context.initWith(Context::Personalized, GfxAPI::GL);
        window = &context.createWindow(title, size);

        if (!window->init())
        {
            window = nullptr;
            return false;
        }

        render = ddgl::DDRenderDevice::create<ddgl::RenderGL>();

        if (render == nullptr || !render->init())
        {
            shutdown();
            return false;
        }

        App::setRenderContext(render);

        return true;

        // if (!window->init())
        // {
        //     window = nullptr;
        //     return false;
        // }

        // render = ddgl::DDRenderDevice::create<ddgl::RenderGL>();
        // App::setRenderContext(render);

        // if (!render->init())
        // {
        //     shutdown();
        //     return false;
        // }

        // return true;
    }

    void PlatformTestContext::shutdown()
    {
        if (window)
        {
            window->Quit();
            window = nullptr;
            render.reset();
            return;
        }

        if (render)
        {
            render->shutdown();
            render.reset();
            render = nullptr;
        }
    }

}
