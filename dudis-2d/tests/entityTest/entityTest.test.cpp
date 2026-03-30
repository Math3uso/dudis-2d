#include <catch2/catch_test_macros.hpp>

#include "dudis2d/dudis2d.h"
#include "dudis2d/debug.h"

using namespace dudis;

TEST_CASE("EntityTest test")
{
    SECTION("It should be able to create a entity")
    {

        auto entity = Entity::create("entity");

        REQUIRE(entity->getTag() == "entity");
    }

    SECTION("It should be able to add a child in entity")
    {

        auto entity = Entity::create("entity");
        auto entity2 = Entity::create("entity2");

        entity->addChild(entity2);

        REQUIRE(entity->getChildren().size() == 1);
    }

    SECTION("It should be able to remove a child in entity")
    {

        auto entity = Entity::create("entity");
        auto entity2 = Entity::create("entity2");

        entity->addChild(entity2);

        entity->removeChild();

        REQUIRE(entity->getChildren().size() == 0);
    }

    SECTION("It should be able to remove a child in entity by tag")
    {

        auto entity = Entity::create("entity");
        auto entity2 = Entity::create("entity2");

        entity->addChild(entity2);

        entity->removeChild("entity2");

        REQUIRE(entity->getChildren().size() == 0);
    }

    SECTION("It should be able to draw a entity with z Order")
    {

        auto entity = Entity::create("entity");
        auto entity2 = Entity::create("entity2");

        entity->setZOrder(10);
        entity2->setZOrder(1);

        entity->addChild(entity2);

        REQUIRE(entity2->getZOrder() == 11);
    }

    SECTION("It should propagate parent zOrder by delta across multiple updates")
    {
        auto parent = Entity::create("parent");
        auto child = Entity::create("child");

        parent->setZOrder(10);
        child->setZOrder(50);
        parent->addChild(child);

        REQUIRE(parent->getZOrder() == 10);
        REQUIRE(child->getZOrder() == 60);

        parent->setZOrder(200);
        REQUIRE(parent->getZOrder() == 200);
        REQUIRE(child->getZOrder() == 250);

        parent->setZOrder(300);
        REQUIRE(parent->getZOrder() == 300);
        REQUIRE(child->getZOrder() == 350);
    }

    SECTION("It should propagate zOrder recursively to grandchildren")
    {
        auto parent = Entity::create("parent");
        auto child = Entity::create("child");
        auto grandChild = Entity::create("grandChild");

        parent->setZOrder(10);
        child->setZOrder(50);
        grandChild->setZOrder(5);

        parent->addChild(child);
        child->addChild(grandChild);

        REQUIRE(parent->getZOrder() == 10);
        REQUIRE(child->getZOrder() == 60);
        REQUIRE(grandChild->getZOrder() == 65);

        parent->setZOrder(200);
        REQUIRE(child->getZOrder() == 250);
        REQUIRE(grandChild->getZOrder() == 255);

        parent->setZOrder(300);
        REQUIRE(child->getZOrder() == 350);
        REQUIRE(grandChild->getZOrder() == 355);
    }
}
