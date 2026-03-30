#include "support/test_context.h"

#include "support/test_paths.h"

namespace dudis::tests
{
bool TestContext::init()
{
    manager = std::make_unique<SceneManager>();
    window = std::make_unique<Window>(SizeI(800, 600), "dudis-2d tests");

    if (!window->init())
    {
        window.reset();
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
    window.reset();
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
    return DDRectangle::create(Size(100, 100), Vec2(300, 200));
}

std::shared_ptr<Sprite> makePlayerSprite(const Size &size)
{
    const auto path = assetPath("player.png");
    return Sprite::create(path.c_str(), size);
}
} // namespace dudis::tests
