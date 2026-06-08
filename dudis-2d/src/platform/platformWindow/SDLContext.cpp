#include <iostream>
#include "SDL3/SDL.h"
// #include "glad/glad.h"
#include "dudis2d/platform/platformWindow/SDLContext.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/platform/input/input.h"
#include "dudis2d/platform/input/sdlInputBackend.h"
#include <algorithm>

using namespace std;
using namespace dudis;

namespace
{
    constexpr double MAX_DELTA_TIME_SECONDS = 0.25;

    SDL_DisplayID resolveDisplayId(uint32_t display)
    {
        if (display != 0 && SDL_GetDisplayName(display) != nullptr)
        {
            return static_cast<SDL_DisplayID>(display);
        }

        int displayCount = 0;
        SDL_DisplayID *displays = SDL_GetDisplays(&displayCount);
        if (displays == nullptr)
        {
            return 0;
        }

        SDL_DisplayID resolvedDisplay = 0;
        if (display < static_cast<uint32_t>(displayCount))
        {
            resolvedDisplay = displays[display];
        }

        SDL_free(displays);
        return resolvedDisplay;
    }
}

SDLContext::SDLContext(const std::string &title, const SizeI &size) : _title(title), _size(size) {}
SDLContext::SDLContext(GfxAPI api) : _renderApi(api) {}

bool SDLContext::init()
{
    if (_initialized)
    {
        return false;
    }

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL video: %s\n", SDL_GetError());
        return false;
    }

    if (_renderApi == GfxAPI::GL)
    {

        Log::Info("[INFO] RENDER_API GL");

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        _windowRef = SDL_CreateWindow(_title.c_str(), _size.w, _size.h, SDL_WINDOW_OPENGL);

        if (_windowRef == nullptr)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            return false;
        }

        _context = SDL_GL_CreateContext((SDL_Window *)_windowRef);

        if (!_context)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                         "Could not create OpenGL context: %s", SDL_GetError());
            return false;
        }

        Log::Info("[INFO] contexto criado");

        if (!SDL_GL_MakeCurrent((SDL_Window *)_windowRef, (SDL_GLContext)_context))
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                         "Could not make OpenGL context current: %s", SDL_GetError());
            return false;
        }

        Log::Success("Window GL Context is Ready");

        Log::Info("[INFO] init render");

        // if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        // {
        //     SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load glad: %s", SDL_GetError());
        //     return false;
        // }
    }

    _done = false;
    _initialized = true;
    _size = getSize();
    _performanceFrequency = SDL_GetPerformanceFrequency();
    _lastTicks = SDL_GetPerformanceCounter();
    _deltaTime = 0.0f;

    if (_fullscreen)
    {
        setFullscreen(true);
    }

    return _initialized;
}

void SDLContext::shutdown()
{

    Log::Info("[INFO] shutdown in SDL CONTEXT");

    if (!_initialized)
    {
        return;
    }

    SDL_DestroyWindow(reinterpret_cast<SDL_Window *>(_windowRef));
    _windowRef = nullptr;
    _initialized = false;
    _fullscreen = false;
    _done = true;
    _lastTicks = 0;
    _performanceFrequency = 0;
    _deltaTime = 0.0f;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

bool SDLContext::isOpen() const
{
    return _initialized && !_done && _windowRef != nullptr;
}

bool SDLContext::isReady() const
{
    return _initialized;
}

bool SDLContext::shouldClose() const
{
    if (!_initialized)
    {
        return true;
    }

    return _done;
}

void SDLContext::setTitle(const std::string &title)
{
    _title = title;
    if (_initialized)
    {
        SDL_SetWindowTitle(reinterpret_cast<SDL_Window *>(_windowRef), _title.c_str());
    }
}

void SDLContext::setSize(SizeI size)
{
    _size = SizeI(size.w, size.h);

    if (!_initialized)
    {
        return;
    }

    SDL_Window *window = reinterpret_cast<SDL_Window *>(_windowRef);
    if (SDL_SetWindowSize(window, size.w, size.h))
    {
        SDL_SyncWindow(window);
        _size = getSize();
    }
}

void SDLContext::setFullscreen(bool fullscreen)
{
    _fullscreen = fullscreen;

    if (!_initialized)
    {
        return;
    }

    SDL_Window *window = reinterpret_cast<SDL_Window *>(_windowRef);
    if (SDL_SetWindowFullscreen(window, fullscreen))
    {
        SDL_SyncWindow(window);
        _size = getSize();
    }
}

uint32_t SDLContext::getCurrentDisplay()
{
    if (!_initialized || _windowRef == nullptr)
    {
        return 0;
    }

    return SDL_GetDisplayForWindow(reinterpret_cast<SDL_Window *>(_windowRef));
}

uint32_t SDLContext::getDisplayCount()
{
    int displayCount = 0;
    SDL_DisplayID *displays = SDL_GetDisplays(&displayCount);
    if (displays == nullptr)
    {
        return 0;
    }

    SDL_free(displays);
    return static_cast<uint32_t>(displayCount);
}

const char *SDLContext::getDisplayName(uint32_t display)
{
    SDL_DisplayID displayId = resolveDisplayId(display);
    if (displayId == 0)
    {
        return nullptr;
    }

    return SDL_GetDisplayName(displayId);
}

SizeI SDLContext::getDisplaySize(uint32_t display)
{
    SDL_DisplayID displayId = resolveDisplayId(display);
    if (displayId == 0)
    {
        return SizeI(0, 0);
    }

    SDL_Rect rect;
    if (!SDL_GetDisplayBounds(displayId, &rect))
    {
        return SizeI(0, 0);
    }

    return SizeI(rect.w, rect.h);
}

void SDLContext::setFPSLimit(uint32_t fps)
{
    if (!_initialized)
    {
        return;
    }

    if (fps == 0)
    {
        SDL_GL_SetSwapInterval(0);
        return;
    }

    SDL_GL_SetSwapInterval(1);
}

void SDLContext::setWindowPos(Vec2 pos)
{
    if (!_initialized || _windowRef == nullptr)
    {
        return;
    }

    SDL_Window *window = reinterpret_cast<SDL_Window *>(_windowRef);
    if (SDL_SetWindowPosition(window, static_cast<int>(pos.x), static_cast<int>(pos.y)))
    {
        SDL_SyncWindow(window);
    }
}

SizeI SDLContext::getSize() const
{
    if (!_initialized || _windowRef == nullptr)
    {
        return _size;
    }

    int width = _size.w;
    int height = _size.h;
    if (!SDL_GetWindowSize(reinterpret_cast<SDL_Window *>(_windowRef), &width, &height))
    {
        return _size;
    }

    return SizeI(width, height);
}

void SDLContext::eventListener()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            _done = true;
        }
        else if (event.type == SDL_EVENT_WINDOW_RESIZED)
        {
            _size = SizeI(event.window.data1, event.window.data2);
        }

        auto *inputBackend = dynamic_cast<dudis::SDLInputBackend *>(Input::getBackend());
        if (inputBackend)
        {
            inputBackend->handleEvent(event);
        }
    }
}

void SDLContext::swapBuffers()
{
    SDL_GL_SwapWindow((SDL_Window *)_windowRef);
    updateFrameTime();
}

uint64_t SDLContext::getTime()
{
    if (!_initialized)
    {
        return 0;
    }

    return SDL_GetTicks();
}

void SDLContext::updateFrameTime()
{
    if (!_initialized)
    {
        _deltaTime = 0.0f;
        return;
    }

    if (_performanceFrequency == 0)
    {
        _performanceFrequency = SDL_GetPerformanceFrequency();
        if (_performanceFrequency == 0)
        {
            _deltaTime = 0.0f;
            return;
        }
    }

    const uint64_t currentTicks = SDL_GetPerformanceCounter();
    if (_lastTicks == 0)
    {
        _lastTicks = currentTicks;
        _deltaTime = 0.0f;
        return;
    }

    if (currentTicks <= _lastTicks)
    {
        _lastTicks = currentTicks;
        _deltaTime = 0.0f;
        return;
    }

    const double elapsed = static_cast<double>(currentTicks - _lastTicks) /
                           static_cast<double>(_performanceFrequency);
    _deltaTime = static_cast<float>(std::clamp(elapsed, 0.0, MAX_DELTA_TIME_SECONDS));
    _lastTicks = currentTicks;
}

float SDLContext::getFrameTime()
{
    return _deltaTime;
}
