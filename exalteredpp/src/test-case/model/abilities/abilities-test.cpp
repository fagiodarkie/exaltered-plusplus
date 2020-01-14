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
  using namespace character::ability_names;

  SECTION("should save ability in map")
  {
    character::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    character::abilities sut;
    sut[WAR] = character::ability_group(WAR, {ability});
    REQUIRE(sut[WAR].get_ability(TEST_ABILITY_NAME).get_name() == TEST_ABILITY_NAME);
  }

  SECTION("should create correctly from JSON")
  {
    character::abilities stub;
    character::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    stub[WAR] = character::ability_group(WAR, {ability}, {character::specialisation("")});

    character::abilities sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut[WAR].get_ability(TEST_ABILITY_NAME).get_name() == TEST_ABILITY_NAME);
    REQUIRE(sut[WAR].get_abilities().size() == 1);
    REQUIRE(sut[WAR].get_specialisations().size() == 1);
  }
}
