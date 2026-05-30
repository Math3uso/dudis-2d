#pragma once

#include "dudis2d/core/utils/size.h"
#include "dudis2d/platform/platformWindow/platformWindow.h"
#include "dudis2d/core/math/vec2.h"
#include <string>

namespace dudis
{
    class RLContext : public PlatformWindow
    {
    public:
        RLContext() = default;
        RLContext(const std::string &title, const SizeI &size);

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

        SizeI getSize() const override;
        bool shouldClose() const override;

        virtual const char *_getPlatformWindow() override { return "RL"; };

    private:
        std::string _title = "dudis2d";
        SizeI _size = SizeI(0, 0);
        bool _initialized = false;
        bool _fullscreen = false;
    };
}
