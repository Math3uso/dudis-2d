#pragma once

#include "dudis2d/dudis2d.h"
#include "dudis2d/platform/ddWindowContext/ddWindowContext.h"

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
        DDWindowContext windowContext;
        Window *window = nullptr;
        std::unique_ptr<SceneManager> manager;
    };

    dudis::Scope<Scene> makeScene();
    std::shared_ptr<DDRectangle> makeQuadDefault();
    std::shared_ptr<Sprite> makePlayerSprite(const SizeF &size = SizeF(100.f, 100.f));
} // namespace dudis::tests
