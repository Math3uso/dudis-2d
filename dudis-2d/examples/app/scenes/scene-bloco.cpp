#include "scenes/scene-bloco.h"
#include <cmath>
#include "dudis2d/graphics/DDRender/DDRender.h"
#include "scenes/scene1.h"
#include "dudis2d/core/motion/motion.h"

DD_NAMESPACE
DD_RENDER

// Linear interpolation function for older C++ standards
template <typename T>
T lerp(T a, T b, T t)
{
    return a + (b - a) * t;
}

class Bloco3 : public Entity
{
private:
    float velo = 200;
    int dir = 0;
    float t = 0;

    bool start() override
    {

        // this->rotate(100.f);

        // auto bloco = DDRectangle::create(Size(50, 50), Vec2(25, 25));

        auto bloco = Sprite::create("../assets/player.png", Size(100, 100));
        bloco->setCrop(DDRect{0.f, 0.f, 32.f, 32.f});
        //        bloco->setColor(dudis::Color::Red());
        this->addChild(bloco);

        return true;
    }

    void update() override
    {

        // t += (Time::deltaTime / 1) * dir;

        // if (t >= 1.0f)
        // {
        //     t = 1.0f;
        //     dir = -1.0f;
        // }
        // else if (t <= 0.0f)
        // {
        //     t = 0.0f;
        //     dir = 1.0f;
        // }

        // float x = lerp<float>(0, 300, t);
        // setPos(Vec2(x, 0));

        // std::cout << this->isSuspend() << "\n";

        float x = Input::getAxis(Axis::Horizontal) * velo * Time::deltaTime;

        this->translate(Vec2(x, 0));

        // dir = 0;
        // if (dudis::Keyboard::isDown(KeyCode::D))
        // {
        //     dir = 1;
        // }
        // else if (dudis::Keyboard::isDown(KeyCode::A))
        // {
        //     dir = -1;
        // }

        // this->translate(Vec2(velo * Time::deltaTime * dir, 0.0f));
    }

    void onCollisionAABB(Entity *other) override
    {
        if (other)
        {
            puts("colidiu");
        }
    }
};

bool SceneBloco::start()
{
    this->label = "sla";

    auto player = make_shared<Bloco3>();

    auto parent = DDRectangle::create(Size(300, 300), Vec2(0, 0));
    parent->setColor(dudis::Color(60, 0, 190, 255));
    auto mov = Motion::create<Easing::EaseBounce>(Vec2(400, 100), 5.f);
    // parent->addChild(player);

    parent->addMotion(mov);

    this->addChild(player);

    // player->addChild(parent);
    // parent->addChild(player);

    // this->addChild(player);
    // this->addChild(parent);

    // auto tex = res::Texture2D::create("../assets/imgtest.jpg", res::DDTextureFilter::Smooth);
    // auto bg = Sprite::create(nullptr, Size(800, 600), tex);

    // this->addChild(bg);

    // bg->setBlendMode(BlendType::LightAdd);

    // auto parent = DDRectangle::create(Size(400, 400), Vec2(15, 15));
    // parent->setColor(dudis::Color(180, 180, 180, 255));
    // parent->setHiddenOverfflow(true);

    // parent->setBlendMode(BlendType::ColorMultiply);

    // auto bloco = make_shared<Bloco3>();

    // parent->addChild(bloco);
    // this->addChild(parent);

    // auto parent = DDRectangle::create(Size(300, 300), Vec2(25, 25));
    // parent->setHiddenOverfflow(true);
    // parent->setColor(dudis::Color::Red());

    // auto bloco = DDRectangle::create(Size(100, 100), Vec2(10, 10));
    // auto bloco2 = DDRectangle::create(Size(100, 100), Vec2(120, 10));
    // auto bloco3 = DDRectangle::create(Size(100, 100), Vec2(230, 10));
    // auto bloco4 = DDRectangle::create(Size(100, 100), Vec2(350, 10));

    // // parent->addChild(bloco);
    // // parent->addChild(bloco2);

    // bloco3->setBlendMode(BlendType::ColorAdd);

    // this->addChild(bloco);
    // this->addChild(bloco2, 3);
    // this->addChild(bloco3, 2);
    // this->addChild(bloco4, 1);
    // this->addChild(parent);
    // this->addChild(bloco3);

    return true;
}

void SceneBloco::update()
{

    if (Keyboard::isPressed(KeyCode::Space))
    {
        auto bloco = dynamic_pointer_cast<Renderable>(this->getChildren()[0]);
        bloco->isSuspend() ? bloco->resume() : bloco->suspend();

        //  auto scene = Scene::create<Scene1>();
        //  App::getSceneManager().pushScene(move(scene));
        //  PUSH_SCENE(scene);
    }
}
