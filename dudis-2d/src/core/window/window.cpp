#include "dudis2d/core/window/window.h"
#include "../../extern/raygui/raygui.h"
#include "dudis2d/core/log/log.h"
#include "dudis2d/globals/app.h"
#include <box2d/box2d.h>

using namespace dudis;

const int DESIGN_WIDTH = 800;
const int DESIGN_HEIGHT = 600;

Window::Window(SizeI nSize, const char *nTitle) {

  SetTraceLogLevel(LOG_ERROR);

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

      DrawTextureRec(frameBuffer.texture,
                     Rectangle{0, 0, (float)frameBuffer.texture.width,
                               -(float)frameBuffer.texture.height},
                     Vector2{0, 0}, WHITE);

      if (App::windowCallback) {
        App::windowCallback();
      }

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