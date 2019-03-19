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
    sut.write(object);

    REQUIRE(object[serialisation::json_constants::SLOT_NAME] == sut.get_name());
  }

  SECTION("should accept a new attribute")
  {
    character::character sut(CHARACTER_NAME);
    sut.set_attribute(character::attribute_name::STRENGTH, character::attribute(TEST_ATTRIBUTE_NAME));
    character::attribute saved_attribute = sut.get_attribute(character::attribute_name::STRENGTH);
    REQUIRE(QString(saved_attribute) == QString(TEST_ATTRIBUTE_NAME));
  }
}
