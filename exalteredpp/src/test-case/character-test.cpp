#include "../thirdparty/catch/catch.hpp"
#include "character/character.h"
#include "serialisation/json_constants.h"

#define CHARACTER_NAME "test-name"
#define TEST_ATTRIBUTE_NAME "test-attribute"

TEST_CASE("Character")
{
  SECTION("should create new character correctly (name constructor)")
  {
    character::character sut(CHARACTER_NAME);
    REQUIRE(QString(CHARACTER_NAME) == sut.get_name());
  }

  SECTION("should create new character correctly (JSON object constructor)")
  {
    QJsonObject object;
    object.insert(serialisation::json_constants::SLOT_NAME, QJsonValue(CHARACTER_NAME));

    character::character sut(object);
    REQUIRE(QString(CHARACTER_NAME) == sut.get_name());
  }

  SECTION("should save character correctly to JSON object")
  {
    character::character sut(CHARACTER_NAME);
    QJsonObject object;
    sut.write_to_json(object);

    REQUIRE(object[serialisation::json_constants::SLOT_NAME] == sut.get_name());
  }

  SECTION("should accept a new attribute")
  {
    character::character sut(CHARACTER_NAME);
    sut.set_attribute(character::attribute_names::attribute::STRENGTH, character::attribute(TEST_ATTRIBUTE_NAME));
    character::attribute saved_attribute = sut.get_attribute(character::attribute_names::attribute::STRENGTH);
    REQUIRE(saved_attribute.get_name() == TEST_ATTRIBUTE_NAME);
  }

  SECTION("should accept a new ability group")
  {
    character::character sut(CHARACTER_NAME);
    sut.set_ability(character::ability_names::ability::WAR, character::ability_group(TEST_ATTRIBUTE_NAME, character::ability_names::COMBAT));
    character::ability_group saved_ability = sut.get_ability_group(character::ability_names::ability::WAR);
    REQUIRE(saved_ability.get_name() == TEST_ATTRIBUTE_NAME);
  }

  SECTION("should change name when change is issued")
  {
    character::character sut(CHARACTER_NAME);
    sut.set_name(QString(CHARACTER_NAME) + " - edit");
    REQUIRE(sut.get_name() == QString(CHARACTER_NAME) + " - edit");
  }

  SECTION("should save and retrieve correct abilities")
  {
    character::character sut(CHARACTER_NAME);
    sut.set_ability(character::ability_names::ability::CRAFT, character::ability_group("craft", character::ability_names::NARRATIVE, { character::ability("new_ability", 1) }));
    sut.set_ability(character::ability_names::ability::WAR, character::ability_group("war", character::ability_names::COMBAT));
    REQUIRE(sut.get_ability_group(character::ability_names::ability::WAR).get_name() == "war");
    REQUIRE(sut.get_ability(character::ability_names::ability::WAR).get_name() == character::ability_names::ability_declination::NO_DECLINATION);
    REQUIRE(sut.get_ability(character::ability_names::ability::WAR).get_ability_value() == 0);
    REQUIRE(sut.get_ability(character::ability_names::ability::CRAFT, "new_ability").get_name() == "new_ability");
    REQUIRE(sut.get_ability(character::ability_names::ability::CRAFT, "new_ability").get_ability_value() == 1);
  }
}
