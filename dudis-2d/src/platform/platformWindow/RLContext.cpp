#include "dudis2d/platform/platformWindow/RLContext.h"

#include "raylib.h"

namespace dudis
{
    RLContext::RLContext(const std::string &title, const SizeI &size)
        : _title(title), _size(size)
    {
    }

    bool RLContext::init()
    {
        if (_initialized)
        {
            return false;
        }

        SetTraceLogLevel(LOG_ERROR);
        InitWindow(_size.w, _size.h, _title.c_str());

        _initialized = IsWindowReady();
        if (_initialized)
        {
            _size = SizeI(GetScreenWidth(), GetScreenHeight());
        }
        SetTargetFPS(60);
        _windowRef = nullptr;
        return _initialized;
    }

    void RLContext::shutdown()
    {
        if (!_initialized)
        {
            return;
        }

        CloseWindow();
        _initialized = false;
        _fullscreen = false;
    }

    bool RLContext::isOpen() const
    {
        return _initialized && IsWindowReady() && !WindowShouldClose();
    }

    bool RLContext::isReady() const
    {
        return IsWindowReady();
    }

    void RLContext::setTitle(const std::string &title)
    {
        _title = title;

        if (_initialized)
        {
            SetWindowTitle(_title.c_str());
        }
    }

    void RLContext::setSize(SizeI size)
    {
        _size = SizeI(size.w, size.h);

        if (_initialized)
        {
            SetWindowSize(size.w, size.h);
            _size = SizeI(GetScreenWidth(), GetScreenHeight());
        }
    }

    void RLContext::setFullscreen(bool fullscreen)
    {
        if (!_initialized)
        {
            _fullscreen = fullscreen;
            return;
        }

        if (_fullscreen == fullscreen)
        {
            return;
        }

        ToggleFullscreen();
        _fullscreen = fullscreen;
        _size = SizeI(GetScreenWidth(), GetScreenHeight());
    }

    SizeI RLContext::getSize() const
    {
        if (!_initialized)
        {
            return _size;
        }

        return SizeI(GetScreenWidth(), GetScreenHeight());
    }

    uint32_t RLContext::getCurrentDisplay()
    {
        if (!_initialized)
        {
            return 0;
        }
        return GetCurrentMonitor();
    }

    uint32_t RLContext::getDisplayCount()
    {
        if (!_initialized)
        {
            return 0;
        }
        return GetMonitorCount();
    }

    const char *RLContext::getDisplayName(uint32_t display)
    {
        if (!_initialized)
        {
            return nullptr;
        }
        return GetMonitorName(display);
    }
    SizeI RLContext::getDisplaySize(uint32_t display)
    {
        if (!_initialized)
        {
            return SizeI(0, 0);
        }
        SizeI size;

        size.w = GetMonitorWidth(display);
        size.h = GetMonitorHeight(display);
        return size;
    }

    void RLContext::setFPSLimit(uint32_t fps)
    {
        if (!_initialized)
        {
            return;
        }

        SetTargetFPS(fps);
        return;
    };

    void RLContext::setWindowPos(Vec2 pos)
    {
        if (!_initialized)
        {
            return;
        }
        SetWindowPosition(pos.x, pos.y);
        return;
    }

    bool RLContext::shouldClose() const
    {
        if (!_initialized)
        {
            return true;
        }

        return WindowShouldClose();
    }
}
