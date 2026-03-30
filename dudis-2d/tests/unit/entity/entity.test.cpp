#include <catch2/catch_test_macros.hpp>

#include "dudis2d/dudis2d.h"

using namespace dudis;

TEST_CASE("entity creation keeps the tag", "[unit]")
{
    const auto entity = Entity::create("entity");
    REQUIRE(entity->getTag() == "entity");
}

TEST_CASE("entity child management updates the list", "[unit]")
{
    auto entity = Entity::create("entity");
    auto child = Entity::create("entity2");

    entity->addChild(child);
    REQUIRE(entity->getChildren().size() == 1);

    entity->removeChild();
    REQUIRE(entity->getChildren().empty());

    entity->addChild(child);
    entity->removeChild("entity2");
    REQUIRE(entity->getChildren().empty());
}

TEST_CASE("entity z-order is propagated to children", "[unit]")
{
    auto parent = Entity::create("parent");
    auto child = Entity::create("child");

    parent->setZOrder(10);
    child->setZOrder(50);
    parent->addChild(child);

    REQUIRE(parent->getZOrder() == 10);
    REQUIRE(child->getZOrder() == 60);

    parent->setZOrder(200);
    REQUIRE(child->getZOrder() == 250);

    parent->setZOrder(300);
    REQUIRE(child->getZOrder() == 350);
}

TEST_CASE("entity z-order is propagated recursively", "[unit]")
{
    auto parent = Entity::create("parent");
    auto child = Entity::create("child");
    auto grandChild = Entity::create("grandChild");

    parent->setZOrder(10);
    child->setZOrder(50);
    grandChild->setZOrder(5);

    parent->addChild(child);
    child->addChild(grandChild);

    REQUIRE(child->getZOrder() == 60);
    REQUIRE(grandChild->getZOrder() == 65);

    parent->setZOrder(200);
    REQUIRE(child->getZOrder() == 250);
    REQUIRE(grandChild->getZOrder() == 255);

    parent->setZOrder(300);
    REQUIRE(child->getZOrder() == 350);
    REQUIRE(grandChild->getZOrder() == 355);
}
