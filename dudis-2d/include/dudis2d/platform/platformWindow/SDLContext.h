#pragma once

#include "dudis2d/platform/platformWindow/platformWindow.h"
#include "dudis2d/platform/ddWindowContext/contextConfig.h"
#include <SDL3/SDL_opengl.h>

namespace dudis
{
    class SDLContext : public PlatformWindow
    {
    public:
        SDLContext() = default;
        SDLContext(const std::string &title, const SizeI &size);
        SDLContext(GfxAPI gfx);

        bool init() override;
        void shutdown() override;
        bool isOpen() const override;
        bool isReady() const override;

        void setTitle(const std::string &title) override;
        void setSize(SizeI size) override;
        void setFullscreen(bool fullscreen) override;

        virtual uint32_t getCurrentDisplay() override;
        virtual uint32_t getDisplayCount() override;
        virtual const char *getDisplayName(uint32_t display) override;
        virtual SizeI getDisplaySize(uint32_t display) override;
        virtual void setFPSLimit(uint32_t fps) override;
        virtual void setWindowPos(Vec2 pos) override;

        virtual const char *_getPlatformWindow() override { return "SDL"; };

        // temp
        virtual void eventListener() override;
        virtual void swapBuffers() override;

        SizeI getSize() const override;
        bool shouldClose() const override;

    private:
        std::string _title = "dudis2d";
        SizeI _size = SizeI(0, 0);
        bool _initialized = false;
        bool _fullscreen = false;
        bool _contextReady = false;
        GfxAPI _renderApi;
        bool _dirty = false;

        void *_context;
    };
}
