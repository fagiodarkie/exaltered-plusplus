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

  SECTION("newly created character should have all attributes set")
  {
    character::character sut(CHARACTER_NAME);
    for (character::attribute_name att_name: character::ATTRIBUTE_NAME.keys() )
      {
        REQUIRE(sut.get_attribute(att_name).get_name() == character::ATTRIBUTE_NAME.value(att_name));
      }
  }

  SECTION("newly created character should have all abilities set")
  {
    character::character sut(CHARACTER_NAME);
    for (character::ability_name ab_name: character::ABILITY_NAME.keys() )
      {
        REQUIRE(sut.get_ability(ab_name).get_name() == character::ABILITY_NAME.value(ab_name));
      }
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
    sut.set_attribute(character::attribute_name::STRENGTH, character::attribute(TEST_ATTRIBUTE_NAME));
    character::attribute saved_attribute = sut.get_attribute(character::attribute_name::STRENGTH);
    REQUIRE(saved_attribute.get_name() == TEST_ATTRIBUTE_NAME);
  }

  SECTION("should accept a new ability group")
  {
    character::character sut(CHARACTER_NAME);
    sut.set_ability(character::ability_name::WAR, character::ability_group(TEST_ATTRIBUTE_NAME));
    character::ability_group saved_ability = sut.get_ability_group(character::ability_name::WAR);
    REQUIRE(saved_ability.get_name() == TEST_ATTRIBUTE_NAME);
  }

  SECTION("should change name when change is issued")
  {
    character::character sut(CHARACTER_NAME);
    sut.set_name(QString(CHARACTER_NAME) + " - edit");
    REQUIRE(sut.get_name() == QString(CHARACTER_NAME) + " - edit");
  }
}
