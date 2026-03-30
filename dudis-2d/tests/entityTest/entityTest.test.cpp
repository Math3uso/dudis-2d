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
}
