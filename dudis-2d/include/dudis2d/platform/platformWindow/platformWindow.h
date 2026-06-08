#pragma once

#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/core/math/vec2.h"
#include <string>
#include <cstdint>
#include <memory>

namespace dudis
{
    class PlatformWindow
    {
    protected:
        void *_windowRef;
        bool _done = false;

    public:
        virtual ~PlatformWindow() = default;

        virtual bool init() = 0;
        virtual void shutdown() = 0;
        virtual bool isOpen() const = 0;
        virtual bool isReady() const = 0;

        virtual void setTitle(const std::string &title) = 0;
        virtual void setFullscreen(bool fullscreen) = 0;

        virtual SizeI getSize() const = 0;
        virtual void setSize(SizeI size) = 0;
        virtual uint32_t getCurrentDisplay() = 0;
        virtual uint32_t getDisplayCount() = 0;
        virtual const char *getDisplayName(uint32_t display) = 0;
        virtual SizeI getDisplaySize(uint32_t display) = 0;
        virtual void setFPSLimit(uint32_t fps) = 0;
        virtual void setWindowPos(Vec2 pos) = 0;
        virtual bool renderIsLoad() { return true; };

        virtual void updateFrameTime() = 0;
        virtual float getFrameTime() = 0;
        virtual uint64_t getTime() = 0;

        // temp
        virtual void eventListener() {};
        virtual void swapBuffers() {};
        // debug
        virtual const char *_getPlatformWindow() { return "unknown"; };

        virtual bool shouldClose() const = 0;

        // for tests using SDL, this is used to bypass the need for a window in headless environments. Not intended for general use.
        static std::unique_ptr<PlatformWindow> _create();
    };

#define CONTEXT_IS_INIT(value)  \
    do                          \
    {                           \
        if (this->_initialized) \
        {                       \
            return (value);     \
        }                       \
    } while (0)

}
