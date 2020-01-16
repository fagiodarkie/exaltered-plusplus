#include "../thirdparty/catch/catch.hpp"
#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "json_constants.h"

#include <QJsonArray>

#define TEST_ABILITY_NAME "test-ability"
#define TEST_ABILITY_VALUE 1

TEST_CASE("Abilities")
{

  SECTION("should save ability in map")
  {
    ability::ability ability_w(ability::WAR, 2);
    ability::abilities sut;
    sut[ability_w.name()] = ability_w;
    REQUIRE(sut[ability_w.name()].name() == ability_w.name());
    REQUIRE(sut.has(ability::WAR));
    REQUIRE(sut.has(ability_w.name()));
  }

  SECTION("should create correctly from JSON")
  {
    ability::abilities stub;
    ability::ability ability(ability::WAR, TEST_ABILITY_VALUE);
    ability.add("spec", 1);
    stub[ability::WAR] = ability;

    ability::abilities sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut[ability::WAR].name().name() == "War");
    REQUIRE(sut[ability::WAR].specialisations().size() == 1);
  }
}
