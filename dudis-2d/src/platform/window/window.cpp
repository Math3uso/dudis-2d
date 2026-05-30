#include "dudis2d/platform/window/window.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/globals/app.h"
#include "dudis2d/graphics/DDRender/DDRender.h"
#include "dudis2d/graphics/frameQueue/frameQueue.h"
#include "dudis2d/graphics/renderQueue/renderQueue.h"
#include <box2d/box2d.h>
#include "dudis2d/platform/input/input.h"
#include "dudis2d/graphics/ddRenderGroup.h"
#include "dudis2d/globals/time.h"
#include "dudis2d/platform/platformWindow/platformWindow.h"
#include "dudis2d/graphics/ddgl/ddglTypes.h"
#include "dudis2d/platform/input/keyboard.h"

// test
#include "dudis2d/graphics/res/imageLoader.h"

using namespace dudis;

Window::Window(SizeI nSize, const char *nTitle)
{
#ifdef DD_DEBUG
  puts("dudis in debug");
#endif

  // #ifdef DD_RELEASE
  //   puts("dudis in release");
  // #endif

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

  if (_window->init())
  {
    App::setWindow(*this);
    std::cout << _window->_getPlatformWindow() << "\n";

    if (std::string(_window->_getPlatformWindow()) == "SDL")
    {
      Input::setBackend(InputBackendType::SDL);
    }
    else
    {
      Input::setBackend(InputBackendType::RL);
    }

    return true;
  }

  // SetTraceLogLevel(LOG_ERROR);
  // InitWindow(size.w, size.h, title);

  // if (!IsWindowReady())
  // {
  //   return false;
  // }

  // SetTargetFPS(60);
  // App::setWindow(*this);

  return false;
}

// v2
void Window::Running()
{

  auto renderQueue = RenderQueue::create();
  auto DDRender = DDRender::create();

  auto *render = App::getRenderContext();

  ddgl::VertexQuadDataTextured quadData;
  quadData.vertices.push_back({100, 100, 0, 0, dudis::Color::Red().packed()});
  quadData.vertices.push_back({200, 100, 1, 0, dudis::Color::Green().packed()});
  quadData.vertices.push_back({200, 200, 1, 1, dudis::Color::Blue().packed()});
  quadData.vertices.push_back({100, 200, 0, 1, dudis::Color::White().packed()});
  quadData.indices.push_back(0);
  quadData.indices.push_back(1);
  quadData.indices.push_back(2);
  quadData.indices.push_back(2);
  quadData.indices.push_back(3);
  quadData.indices.push_back(0);

  quadData.textureId = ddgl::DD_WHITE_TEXTURE_ID;

  // auto img = ImageLoader::loadFromFile("../assets/player.png");

  while (!_window->shouldClose())
  {

    _window->eventListener();

    Input::update();

    render->beginFrame();

    render->submit(quadData);

    render->endFrame();

    _window->swapBuffers();

    // Input::update();

    // // fix
    // // App::processMainThreadQueue();

    // Time::deltaTime = GetFrameTime() * Time::timeScele;

    // int currentWidth = GetScreenWidth();
    // int currentHeight = GetScreenHeight();

    // if (renderManager)
    // {

    //   BeginDrawing();

    //   ClearBackground(rl::rlColor{clearColor.r, clearColor.g, clearColor.b, clearColor.a});

    //   renderManager->applyChangeScene();

    //   if (renderManager->getTotalScenes() > 0)
    //   {
    //     auto scene = renderManager->getCurrentScene();

    //     renderQueue->clear();
    //     scene->setDeltaTimeInRoot(Time::deltaTime);
    //     scene->collectRenderCommands(renderQueue.get());
    //     // DDRenderGroup::initPipeline(renderQueue.get());
    //     DDRender->draw(renderQueue->getCommands(), renderQueue.get());
    //   }

    //   EndDrawing();

    //   continue;
    // }
  }

  puts("preparando pra fechar");

  if (renderManager)
  {
    renderManager->dispose();
  }

  this->_close();

  puts("fechando janela");

  // CloseWindow();
  // _window->shutdown();
  this->Quit();
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
  // CloseWindow();
  _window->shutdown();
  App::release();
}

void Window::SetRenderManager(SceneManager &renderer)
{
  renderManager = &renderer;
  return;
}

// const ResolutionProps Window::_getResoltionProps()
// {
//   float scale = fminf((float)size.w / _resolution.size.w,
//                       (float)size.h / _resolution.size.h);
//   int offsetX = (size.w - (_resolution.size.w * scale)) / 2;
//   int offsetY = (size.h - (_resolution.size.h * scale)) / 2;

//   return ResolutionProps(Vec2{(float)offsetX, (float)offsetY}, scale);
// }

void Window::setSize(const SizeI &nSize)
{
  size = nSize;

  _window->setSize(size);
  // SetWindowSize(size.w, size.h);
  if (_center)
  {
    this->_centerWindow();
  }
}

void Window::_centerWindow()
{
  auto display = _window->getCurrentDisplay();

  auto screen = _window->getDisplaySize(display);

  auto windowSize = _window->getSize();

  int posX = (screen.w - windowSize.w) / 2;
  int posY = (screen.h - windowSize.h) / 2;

  _window->setWindowPos(Vec2((float)posX, (float)posY));
}

void Window::setPlatformWindow(PlatformWindow *window)
{
  _window = window;
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
  // this->SetFPS(60);

  // auto renderQueue = RenderQueue::create();
  // auto DDRender = DDRender::create();

  // for (int i = 0; i < seconds && !WindowShouldClose(); i++)
  // {
  //   Input::update();

  //   BeginDrawing();

  //   ClearBackground(rl::rlColor{clearColor.r, clearColor.g, clearColor.b, clearColor.a});

  //   renderManager->applyChangeScene();

  //   if (renderManager->getTotalScenes() > 0)
  //   {
  //     auto scene = renderManager->getCurrentScene();

  //     renderQueue->clear();
  //     scene->collectRenderCommands(renderQueue.get());
  //     DDRender->draw(renderQueue->getCommands(), renderQueue.get());
  //   }

  //   EndDrawing();
  // }
  // this->release();
  // this->Quit();
}
