#include "../thirdparty/catch/catch.hpp"
#include "abilities/abilities.h"
#include "abilities/ability_group.h"
#include "abilities/ability.h"
#include "json_constants.h"

#include <QJsonArray>

#define TEST_ABILITY_NAME "test-attribute"
#define TEST_ABILITY_VALUE 1

using namespace character::ability_names;

TEST_CASE("Abilities")
{
  SECTION("should save ability in map")
  {
    character::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    character::abilities sut;
    sut.insert(ability::WAR, character::ability_group(TEST_ABILITY_NAME, ability_category::COMBAT, {ability}));
    REQUIRE(sut.value(ability::WAR).get_name() == TEST_ABILITY_NAME);
  }

  SECTION("should create correctly from JSON")
  {
    QJsonObject inner_obj;
    character::ability_group inner_group (TEST_ABILITY_NAME, ability_category::COMBAT, {character::ability(), character::ability()}, {character::specialisation("")});
    inner_group.write_to_json(inner_obj);

    QJsonObject from;
    from[ABILITY_NAME.value(ability::WAR)] = inner_obj;
    character::abilities sut;
    sut.read_from_json(from);
    REQUIRE(sut.value(ability::WAR).get_name() == TEST_ABILITY_NAME);
    REQUIRE(sut.value(ability::WAR).get_abilities().size() == inner_group.get_abilities().size());
    REQUIRE(sut.value(ability::WAR).get_specialisations().size() == inner_group.get_specialisations().size());
  }

  SECTION("should write correctly to JSON")
  {
    character::abilities sut;
    character::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    sut.insert(ability::WAR, character::ability_group(TEST_ABILITY_NAME, ability_category::COMBAT, {ability}, {character::specialisation("")}));
    QJsonObject from;
    sut.write_to_json(from);
    QJsonObject war_obj = from[TEST_ABILITY_NAME].toObject();
    REQUIRE(war_obj[serialisation::json_constants::SLOT_NAME].toString() == TEST_ABILITY_NAME);
    REQUIRE(war_obj[serialisation::json_constants::SLOT_ABILITIES].toArray().count() == 1);
    REQUIRE(war_obj[serialisation::json_constants::SLOT_SPECIALISATIONS].toArray().count() == 1);
  }
}
