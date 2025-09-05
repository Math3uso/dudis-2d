#include "scenes/scene-layout/sceneLayout.h"
#include "dudis2d/graphics.h"

void SceneLayout::start() {
  label = "scene layout";

  auto sprite = new dudis::Sprite("../assets/Purple.png", {64, 64});
  sprite->setOrigin({32, 32});

  auto texture = new dudis::FrameBuffer({500, 500});
  texture->setPos({150, 50});

  auto textureSize = texture->getSize();

  int tilesX = (int)ceil(textureSize.w + 64 / 64.f);
  int tilesY = (int)ceil(textureSize.h + 64 / 64.f);

  texture->draw([&]() {
    for (int y = 0; y < tilesY; y++) {
      for (int x = 0; x < tilesX; x++) {
        sprite->setPos({x * 64.f, y * 64.f});
        sprite->render();
      }
    }
  });

  auto shader = new Shader(LoadShader(0, "../shaders/teste2.frag"));

  int *iResolution = new int(GetShaderLocation(*shader, "iResolution"));

  int *uTexture = new int(GetShaderLocation(*shader, "uTexture"));

  int *time = new int(GetShaderLocation(*shader, "time"));

  SetTraceLogLevel(LOG_ALL);

  texture->makeFrameBuffer();

  App::SceneDraw([texture, iResolution, shader, uTexture, time]() {
    Vector2 resolution = {(float)GetScreenWidth(), (float)GetScreenHeight()};

    float deltaTime = GetTime();

    BeginShaderMode(*shader);
    SetShaderValue(*shader, *iResolution, &resolution, SHADER_UNIFORM_VEC2);
    SetShaderValueTexture(*shader, *uTexture, texture->getTexture().texture);
    SetShaderValue(*shader, *time, &deltaTime, SHADER_UNIFORM_FLOAT);

    texture->render();

    EndShaderMode();
  });

  this->releaseAfterUse([texture, shader, iResolution, time, sprite]() {
    UnloadShader(*shader);
    delete texture;
    delete shader;
    delete iResolution;
    delete time;
    delete sprite;
  });
}

void SceneLayout::update() {}