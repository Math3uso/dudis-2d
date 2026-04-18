#include "dudis2d/core/window/window.h"
#include "../../extern/raygui/raygui.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/globals/app.h"
#include "dudis2d/graphics/DDRender/DDRender.h"
#include "dudis2d/graphics/frameQueue/frameQueue.h"
#include "dudis2d/graphics/renderQueue/renderQueue.h"
#include <box2d/box2d.h>
#include "dudis2d/core/input/input.h"
#include "dudis2d/graphics/ddRenderGroup.h"
#include "dudis2d/globals/time.h"

using namespace dudis;

Window::Window(SizeI nSize, const char *nTitle)
{

#ifdef DD_DEBUG
  puts("dudis in debug");
#endif

  // #ifdef DD_RELEASE
  //   puts("dudis in release");
  // #endif

  // SetTraceLogLevel(LOG_ERROR);

  size = nSize;
  title = nTitle;
}

bool Window::init()
{

  // #if defined(_WIN32)
  // #ifdef BUILD_MY_ENGINE
  // #define MY_ENGINE_API __declspec(dllexport)
  // #else
  // #define MY_ENGINE_API __declspec(dllimport)
  // #endif
  // #elif defined(__GNUC__) || defined(__clang__)
  // // No Linux/macOS, usamos 'visibility'
  // #define MY_ENGINE_API __attribute__((visibility("default")))
  // #else
  // #define MY_ENGINE_API
  // #endif

  SetTraceLogLevel(LOG_ERROR);
  InitWindow(size.w, size.h, title);

  if (!IsWindowReady())
  {
    return false;
  }

  SetTargetFPS(60);
  App::setWindow(*this);

  return true;
}

// v2
void Window::Running()
{

  auto renderQueue = RenderQueue::create();
  auto DDRender = DDRender::create();

  while (!WindowShouldClose())
  {

    Input::update();

    // fix
    // App::processMainThreadQueue();

    Time::deltaTime = GetFrameTime() * Time::timeScele;

    int currentWidth = GetScreenWidth();
    int currentHeight = GetScreenHeight();

    if (renderManager)
    {

      BeginDrawing();

      ClearBackground(rl::rlColor{clearColor.r, clearColor.g, clearColor.b, clearColor.a});

      renderManager->applyChangeScene();

      if (renderManager->getTotalScenes() > 0)
      {
        auto scene = renderManager->getCurrentScene();

        renderQueue->clear();
        scene->setDeltaTimeInRoot(Time::deltaTime);
        scene->collectRenderCommands(renderQueue.get());
        // DDRenderGroup::initPipeline(renderQueue.get());
        DDRender->draw(renderQueue->getCommands(), renderQueue.get());
      }

      EndDrawing();

      continue;
    }
  }

  puts("preparando pra fechar");

  if (renderManager)
  {
    renderManager->dispose();
  }

  this->_close();

  puts("fechando janela");

  CloseWindow();
}

void Window::release()
{

  if (renderManager)
  {
    renderManager->dispose();
    App::release();
  }
}

void Window::Quit()
{
  this->_close();
  CloseWindow();
}

void Window::SetRenderManager(SceneManager &renderer)
{
  renderManager = &renderer;
  return;
}

const ResolutionProps Window::_getResoltionProps()
{
  float scale = fminf((float)size.w / _resolution.size.w,
                      (float)size.h / _resolution.size.h);
  int offsetX = (size.w - (_resolution.size.w * scale)) / 2;
  int offsetY = (size.h - (_resolution.size.h * scale)) / 2;

  return ResolutionProps(Vec2{(float)offsetX, (float)offsetY}, scale);
}

void Window::setSize(const SizeI &nSize)
{
  size = nSize;

  SetWindowSize(size.w, size.h);
  if (_center)
  {
    this->_centerWindow();
  }
}

void Window::_centerWindow()
{
  int screenWidth = GetMonitorWidth(GetCurrentMonitor());
  int screenHeight = GetMonitorHeight(GetCurrentMonitor());

  int windowWidth = GetScreenWidth();
  int windowHeight = GetScreenHeight();

  int posX = (screenWidth - windowWidth) / 2;
  int posY = (screenHeight - windowHeight) / 2;

  SetWindowPosition(posX, posY);
}

void Window::_close()
{
  while (!_closeCallback.empty())
  {
    auto close = _closeCallback.front();
    close();
    _closeCallback.pop();
  }
}

void Window::runByFrames(int seconds)
{
  this->SetFPS(60);

  auto renderQueue = RenderQueue::create();
  auto DDRender = DDRender::create();

  for (int i = 0; i < seconds && !WindowShouldClose(); i++)
  {
    Input::update();

    BeginDrawing();

    ClearBackground(rl::rlColor{clearColor.r, clearColor.g, clearColor.b, clearColor.a});

    renderManager->applyChangeScene();

    if (renderManager->getTotalScenes() > 0)
    {
      auto scene = renderManager->getCurrentScene();

      renderQueue->clear();
      scene->collectRenderCommands(renderQueue.get());
      DDRender->draw(renderQueue->getCommands(), renderQueue.get());
    }

    EndDrawing();
  }
  // this->release();
  // this->Quit();
}