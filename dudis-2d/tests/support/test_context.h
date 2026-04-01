#pragma once

#include "dudis2d/dudis2d.h"

namespace dudis::tests
{
class TestScene : public Scene
{
public:
    void update() override {}
    bool start() override { return true; }
};

class TestContext
{
public:
    bool init();
    void shutdown();

    void pushScene(dudis::Scope<Scene> scene);
    void pushDrawable(const std::shared_ptr<Renderable> &renderable);
    void runFrames(int frames);

    Window &windowRef() const { return *window; }
    SceneManager &sceneManagerRef() const { return *manager; }

private:
    std::unique_ptr<Window> window;
    std::unique_ptr<SceneManager> manager;
};

dudis::Scope<Scene> makeScene();
std::shared_ptr<DDRectangle> makeQuadDefault();
std::shared_ptr<Sprite> makePlayerSprite(const Size &size = Size(100, 100));
} // namespace dudis::tests
