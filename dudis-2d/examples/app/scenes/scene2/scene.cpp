#include "dudis2d/graphics.h"
#include "models/ground/ground.h"
#include "models/items/apple_item/apple_item.h"
#include "models/player/player.h"
#include "scenes/scene2/scene2.h"

using namespace std;
using namespace dudis;

void Scene2::start() {
  this->addPhysics();
  label = "sceneteste";

  this->showPhysicsDebug = true;

  auto bt2 = Button::create("prev");
  bt2->setPos({250, 100});

  bt2->addEventListnear(
      [=](RenderUI *ref) { App::getSceneManager().popScene(); });

  this->addToRender(bt2);

  auto ground = Ground::create();
  auto player = Player::create();
  auto item = AppleItem::create();

  auto *shader = new Shader(LoadShader(0, "../shaders/teste.frag"));

  sprite = new DDRectangle({100, 100}, {400, 300});
  sprite->setOrigin({50, 50});

  auto *image = new Sprite("../assets/Purple.png", {64, 64});

  int *resolutionLoc = new int(GetShaderLocation(*shader, "iResolution"));
  int *timec = new int(GetShaderLocation(*shader, "time"));
  float *timeValue = new float(GetFrameTime());

  Texture2D *tileBG = new Texture2D(LoadTexture("../assets/Purple.png"));
  RenderTexture2D *bg = new RenderTexture2D(LoadRenderTexture(700, 500));

  BeginTextureMode(*bg);
  ClearBackground(BLACK);
  for (int y = 0; y < 600 / 64; y++) {
    for (int x = 0; x < 800 / 64; x++) {
      DrawTexture(*tileBG, x * 64, y * 64, WHITE);
    }
  }
  EndTextureMode();

  App::SceneDraw([&, shader, resolutionLoc, timeValue, timec, bg, image]() {
    *timeValue = GetTime();

    Vector2 resolution = {(float)GetScreenWidth(), (float)GetScreenHeight()};
    SetShaderValue(*shader, *resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(*shader, *timec, timeValue, SHADER_UNIFORM_FLOAT);

    SetShaderValueTexture(*shader, GetShaderLocation(*shader, "texture0"),
                          bg->texture);

    BeginShaderMode(*shader);

    DrawTextureRec(bg->texture, (Rectangle){0, 0, 800, -600}, (Vector2){0, 0},
                   WHITE);

    // this->sprite->render();

    // image->render();

    EndShaderMode();
  });

  this->releaseAfterUse(
      [resolutionLoc, timeValue, timec, bg, tileBG, shader]() {
        UnloadShader(*shader);
        UnloadRenderTexture(*bg);
        UnloadTexture(*tileBG);
        delete resolutionLoc;
        delete timeValue;
        delete timec;
        delete bg;
        delete tileBG;

        Log::Success("extras REALMENTE deletados");
      });

  this->addModel(item);
  this->addModel(ground);
  this->addModel(player);
}

void Scene2::update() {
  if (IsKeyDown(KEY_D)) {
    this->sprite->translate({10.f, 0});
  } else if (IsKeyDown(KEY_A)) {
    this->sprite->translate({-10.f, 0});
  }
}