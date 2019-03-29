#include "../thirdparty/catch/catch.hpp"
#include "abilities/abilities.h"
#include "abilities/ability_group.h"
#include "abilities/ability.h"
#include "json_constants.h"

#define TEST_ABILITY_NAME "test-attribute"
#define TEST_ABILITY_VALUE 1

TEST_CASE("Abilities")
{
  SECTION("should save ability in map")
  {
    character::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    character::abilities sut;
    sut.insert(character::ability_name::WAR, character::ability_group(TEST_ABILITY_NAME, {ability}));
    REQUIRE(int(sut.value(character::ability_name::WAR).get_ability()) == TEST_ABILITY_VALUE);
    REQUIRE(QString(sut.value(character::ability_name::WAR).get_ability()) == QString(TEST_ABILITY_NAME));
  }

  SECTION("should create correctly from JSON")
  {
    QJsonObject from;
    from[character::ABILITY_NAME.value(character::ability_name::WAR)] = TEST_ABILITY_VALUE;
    character::abilities sut;
    sut.read_from_json(from);
    REQUIRE(sut.value(character::ability_name::WAR).get_ability().get_ability_value() == TEST_ABILITY_VALUE);
  }

  SECTION("should write correctly to JSON")
  {
    character::abilities sut;
    character::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    sut.insert(character::ability_name::WAR, character::ability_group(TEST_ABILITY_NAME, {ability}));
    QJsonObject from;
    sut.write_to_json(from);
    REQUIRE(from[character::ABILITY_NAME.value(character::ability_name::WAR)].toObject()[serialisation::json_constants::SLOT_NAME].toString() == TEST_ABILITY_NAME);
  }
}
