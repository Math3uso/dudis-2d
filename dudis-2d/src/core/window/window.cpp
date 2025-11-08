#include "dudis2d/core/window/window.h"
#include "../../extern/raygui/raygui.h"
// #include "dudis2d/core/debug/dd-debug.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/globals/app.h"
#include <box2d/box2d.h>

using namespace dudis;

Window::Window(SizeI nSize, const char *nTitle) {

  // if constexpr (DDConfig::debugMode) {
  //   puts("modo debug ativado");
  // } else {
  //   puts("debug n ativado");
  // }

  // DD_DEBUG(puts("foi"));

  SetTraceLogLevel(LOG_ERROR);

  _globalCamera = DDCamera();

  size = nSize;
  title = nTitle;

  // float scaleX = 1.0f;
  // float scaleY = 1.0f;

  InitWindow(size.w, size.h, title);

  // camera.target = (Vector2){DESIGN_WIDTH / 2, DESIGN_HEIGHT / 2};
  // camera.offset = (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2};
  // camera.rotation = 0.0f;
  // camera.zoom = 1.0f;

  SetTargetFPS(60);

  App::setWindow(*this);
}

void Window::Running() {

  while (!WindowShouldClose()) {

    int currentWidth = GetScreenWidth();
    int currentHeight = GetScreenHeight();

    RenderTexture2D frameBuffer = {};

    // Size internalSize = _resolution.size;

    if (renderManager) {

      renderManager->applyChangeScene();

      auto currentScene = renderManager->getScene();
      auto replace = renderManager->replaceSceneMode;

      if (renderManager->getTotalScenes() > 0 && replace) {
        const auto scene = renderManager->getCurrentScene();

        if (scene) {
          scene->drawing(frameBuffer, {currentWidth, currentHeight});

          if (currentScene) {
            renderManager->releaseCurrentScene();
          }
        }
      } else {

        currentScene->drawing(frameBuffer, {currentWidth, currentHeight});
      }

      BeginDrawing();

      ClearBackground(WHITE);

      BeginMode2D(_globalCamera.getCameraProps());

      this->_drawTextureFromRenderManager(frameBuffer);

      if (App::windowCallback) {
        App::windowCallback();
      }

      if (_globalCamera.isDebugMode()) {
        _globalCamera.drawDebugInfo();
      }

      EndMode2D();

      EndDrawing();

      continue;
      //==============
    }

    BeginDrawing();
    ClearBackground(clearColor);

    EndDrawing();
  }

  puts("preparando pra fechar");

  if (renderManager) {
    renderManager->dispose();
  }

  puts("fechando janela");

  CloseWindow();
}

void Window::Quit() { CloseWindow(); }

void Window::SetRenderManager(SceneManager &renderer) {
  renderManager = &renderer;
  return;
}

const ResolutionProps Window::_getResoltionProps() {
  float scale = fminf((float)size.w / _resolution.size.w,
                      (float)size.h / _resolution.size.h);
  int offsetX = (size.w - (_resolution.size.w * scale)) / 2;
  int offsetY = (size.h - (_resolution.size.h * scale)) / 2;

  return ResolutionProps(Vec2{(float)offsetX, (float)offsetY}, scale);
}

void Window::_drawTextureFromRenderManager(const RenderTexture2D &frameBuffer) {

  if (this->_resolution._policy == ResolutionPolicy::None) {
    DrawTextureRec(frameBuffer.texture,
                   Rectangle{0, 0, (float)frameBuffer.texture.width,
                             -(float)frameBuffer.texture.height},
                   Vector2{0, 0}, WHITE);
    return;
  }

  auto resolutionProps = this->_getResoltionProps();

  auto sizeSrc = Size{frameBuffer.texture.width, frameBuffer.texture.height};

  auto posDest = resolutionProps.offset;
  auto sizeDes = Size{_resolution.size.w * resolutionProps.scale,
                      _resolution.size.h * resolutionProps.scale};

  DrawTexturePro(
      frameBuffer.texture,
      {0, 0, (float)sizeSrc.w,
       -(float)sizeSrc.h}, // tamanho original da textura
      {posDest.x, posDest.y, (float)sizeDes.w,
       (float)
           sizeDes.h}, // tamanho alterado pela resolução (desenhando com scele)
      {0, 0}, 0, WHITE);

  return;
}

void Window::setSize(const Size &nSize) {
  size = nSize;

  SetWindowSize(size.w, size.h);
  if (_center) {
    this->_centerWindow();
  }
}

void Window::_centerWindow() {
  int screenWidth = GetMonitorWidth(GetCurrentMonitor());
  int screenHeight = GetMonitorHeight(GetCurrentMonitor());

  int windowWidth = GetScreenWidth();
  int windowHeight = GetScreenHeight();

  int posX = (screenWidth - windowWidth) / 2;
  int posY = (screenHeight - windowHeight) / 2;

  SetWindowPosition(posX, posY);
}