#include "scenes/scene1.h"

#include <cmath>

#include "raygui.h"
#include "dudis2d/core/events/eventListener.h"
#include "scenes/scene-bloco.h"

DD_PHYSICS
#include <random>

using namespace dudis;

// auto bloco = DDRectangle::create({300, 250}, {200, 150});
// bloco->setColor(RED);

// auto child = DDRectangle::create(Size{100, 100}, Vec2{110, 125});
// child->setOrigin({50, 50});
// bloco->setColor(BLUE);

// // bloco->setTransformType(TransformType::DisableParentTransform);
// // bloco->setOrigin({50, 125});

// auto body = PhysicsComponent::createBoxPhysics(bloco.get(), false, true);
// bloco->addComponent<PhysicsComponent>(body);
// bloco->setOrigin(Vec2{150, 125});

// auto player = Sprite::create("../assets/player.png", Size(100, 100));
// player->setPos(Vec2(10, 10));

bool Scene1::start()
{
    label = "scene1";

    // auto player = DDRectangle::create(Size(300, 300), Vec2(10, 10));
    // player->setColor(dudis::Color::Red());

    // auto teste = DDRectangle::create(Size(100, 100), Vec2(300, 0));

    // // // player->setCrop(DDRect{0, 0, 32, 32});

    // // std::cout << "pos x " << teste->getGlobalPos().x << "\n";
    // // std::cout << "pos x " << teste->getGlobalPos().x << "\n";

    // // player->addChild(teste);

    // std::cout << "pos x " << teste->getGlobalPos().x << "\n";

    // this->addChild(teste);
    // this->addChild(player);

    // if (player->intersectsWith(teste))
    // {
    //     puts("colidiy");
    // }

    // auto player = Sprite::create("../assets/player.png", Size(100, 100), res::TextureFilter::Smooth);
    // player->setCrop(DDRect{0, 0, 32, 32});

    // this->addChild(player);

    auto bloc1 = DDRectangle::create(Size(500, 500), Vec2(10, 10));
    auto bloc2 = DDRectangle::create(Size(100, 100), Vec2(10, 10));
    // auto bloc3 = DDRectangle::create(Size(10, 10), Vec2(0, 0));

    auto bloco3 = DDRectangle::create(Size(100, 100), Vec2(20, 20));

    auto bloco4 = DDRectangle::create(Size(20, 20), Vec2(20, 20));
    auto bloco5 = DDRectangle::create(Size(20, 20), Vec2(25, 25));

    bloc1->setColor(dudis::Color(230, 41, 55, 255));
    bloc2->setColor(dudis::Color::Blue());
    bloco3->setColor(dudis::Color::Green());

    // this->addChild(bloc2, 110);
    // this->addChild(bloc1, 10);

    // for (int i = 0; i < 5000; i++)
    // {
    //     this->addChild(bloc1, i);
    // }

    // // this->addChild(player2);
    // // this->addChild(bloco, 14);

    // // // this->addChild(child, 12);
    bloc1->addChild(bloc2, 10);
    bloc1->addChild(bloco3, 11);

    bloco4->setColor(dudis::Color::Red());
    bloco5->setColor(dudis::Color::Blue());

    bloco3->addChild(bloco5, 15);
    bloco3->addChild(bloco4, 17);

    // for (int i = 0; i < 3000; i++)
    // {
    //     this->addChild(bloc1, i);
    // }

    // this->addChild(bloc1, 12);

    // bloc2->setZOrder(5);
    // bloc2->addChild(bloc3, 10);

    std::cout << "zOrder do 1 " << bloc1->getZOrder() << "\n";
    std::cout << "zOrder do 2 " << bloc2->getZOrder() << "\n";

    std::cout << "zOrder do 4 " << bloco4->getZOrder() << "\n";
    std::cout << "zOrder do 5 " << bloco5->getZOrder() << "\n";
    // std::cout << "zOrder do 3 " << bloc3->getZOrder() << "\n";

    // auto tex = res::Texture2D::create("../assets/player.png");
    // tex.setFilter(res::TextureFilter::Smooth);

    // tex.setWrap(res::TextureWrap::Repeat);

    // auto bg = Sprite::create("", Size(200, 200), tex);
    // bg->setCrop({0, 0, 32, 32});

    // this->addChild(bg);
    return true;
}

void Scene1::update()
{
    if (Keyboard::isPressed(KeyCode::Space))
    {
        App::getSceneManager().popScene();
    }
}
