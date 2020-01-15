#include "../thirdparty/catch/catch.hpp"
#include "abilities/abilities.h"
#include "abilities/ability_group.h"
#include "abilities/ability.h"
#include "json_constants.h"

#include <QJsonArray>

#define TEST_ABILITY_NAME "test-ability"
#define TEST_ABILITY_VALUE 1

TEST_CASE("Abilities")
{

  SECTION("should save ability in map")
  {
    ability::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    ability::abilities sut;
    sut[ability::WAR] = ability::ability_group(ability::WAR, {ability});
    REQUIRE(sut[ability::WAR].get_ability(TEST_ABILITY_NAME).name() == TEST_ABILITY_NAME);
  }

  SECTION("should create correctly from JSON")
  {
    ability::abilities stub;
    ability::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    stub[ability::WAR] = ability::ability_group(ability::WAR, {ability}, {ability::specialisation("")});

    ability::abilities sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut[ability::WAR].get_ability(TEST_ABILITY_NAME).name() == TEST_ABILITY_NAME);
    REQUIRE(sut[ability::WAR].get_abilities().size() == 1);
    REQUIRE(sut[ability::WAR].get_specialisations().size() == 1);
  }
}
