#include "support/test_context.h"

#include "support/test_paths.h"

#include <cstdlib>

namespace dudis::tests
{
    bool TestContext::init()
    {
        if (std::getenv("DISPLAY") == nullptr && std::getenv("WAYLAND_DISPLAY") == nullptr)
        {
            return false;
        }

        manager = std::make_unique<SceneManager>();
        windowContext.initWith();
        window = &windowContext.createWindow("dudis-2d tests", SizeI(800, 600));

        if (!window->init())
        {
            window = nullptr;
            manager.reset();
            return false;
        }

        App::setSceneManager(*manager);
        window->SetRenderManager(*manager);
        return true;
    }

    void TestContext::shutdown()
    {
        if (!window)
        {
            return;
        }

        window->release();
        window->Quit();
        window = nullptr;
        manager.reset();
    }

    void TestContext::pushScene(dudis::Scope<Scene> scene)
    {
        manager->pushScene(std::move(scene));
    }

    void TestContext::pushDrawable(const std::shared_ptr<Renderable> &renderable)
    {
        manager->getCurrentScene()->addChild(renderable);
    }

    void TestContext::runFrames(int frames)
    {
        window->runByFrames(frames);
    }

    dudis::Scope<Scene> makeScene()
    {
        return Scene::create<TestScene>();
    }

    std::shared_ptr<DDRectangle> makeQuadDefault()
    {
        return DDRectangle::create(SizeF(100.f, 100.f), Vec2(300, 200));
    }

    // std::shared_ptr<Sprite> makePlayerSprite(const SizeF &size)
    // {
    //     const auto path = assetPath("player.png");
    //     return Sprite::create(path.string().c_str(), size);
    // }
} // namespace dudis::tests
