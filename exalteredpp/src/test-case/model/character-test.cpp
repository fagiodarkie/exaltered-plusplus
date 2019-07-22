#include "../thirdparty/catch/catch.hpp"
#include "character/character.h"
#include "serialisation/json_constants.h"

#define CHARACTER_NAME "test-name"
#define TEST_ATTRIBUTE_NAME "test-attribute"
#define STANDARD_CHARACTER character::character(CHARACTER_NAME, character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, character::attributes(), character::abilities(), character::virtues::virtues(), character::power::power_container())

/* const QString name,
                                                        const creation::character_type type,
                                                        const exalt::caste caste,
                                                        const attributes attributes,
                                                        const abilities abilities,
                                                        const virtues::virtues virtues,
                                                        const power::power_container power_container)
 */

TEST_CASE("Character")
{
  SECTION("should create new character correctly (name constructor)")
  {
    character::character sut = STANDARD_CHARACTER;
    REQUIRE(sut.get_name() == CHARACTER_NAME);
  }

  SECTION("should create new character correctly (JSON object constructor)")
  {
    character::character stub = STANDARD_CHARACTER;
    character::character sut(stub.serialise());

    REQUIRE(sut.get_name() == stub.get_name());
  }

  SECTION("should accept a new attribute")
  {
    character::character sut = STANDARD_CHARACTER;
    sut.set_attribute(character::attribute_names::attribute::STRENGTH, character::attribute(TEST_ATTRIBUTE_NAME));
    character::attribute saved_attribute = sut.get_attribute(character::attribute_names::attribute::STRENGTH);
    REQUIRE(saved_attribute.get_name() == TEST_ATTRIBUTE_NAME);
  }

  SECTION("should accept a new ability group")
  {
    character::character sut = STANDARD_CHARACTER;
    sut.set_ability(character::ability_names::WAR, character::ability_group(TEST_ATTRIBUTE_NAME, character::ability_names::COMBAT));
    character::ability_group saved_ability = sut.get_ability_group(character::ability_names::WAR);
    REQUIRE(saved_ability.get_name() == TEST_ATTRIBUTE_NAME);
  }

  SECTION("should change name when change is issued")
  {
    character::character sut = STANDARD_CHARACTER;
    sut.set_name(std::string(CHARACTER_NAME) + " - edit");
    REQUIRE(sut.get_name() == std::string(CHARACTER_NAME) + " - edit");
  }

  SECTION("should save and retrieve correct abilities")
  {
    character::character sut = STANDARD_CHARACTER;
    sut.set_ability(character::ability_names::CRAFT, character::ability_group("craft", character::ability_names::NARRATIVE, { character::ability("new_ability", 1) }));
    sut.set_ability(character::ability_names::WAR, character::ability_group("war", character::ability_names::COMBAT));
    REQUIRE(sut.get_ability_group(character::ability_names::WAR).get_name() == "war");
    REQUIRE(sut.get_ability(character::ability_names::WAR).get_name() == character::ability_names::ability_declination::NO_DECLINATION);
    REQUIRE(sut.get_ability(character::ability_names::WAR).get_ability_value() == 0);
    REQUIRE(sut.get_ability(character::ability_names::CRAFT, "new_ability").get_name() == "new_ability");
    REQUIRE(sut.get_ability(character::ability_names::CRAFT, "new_ability").get_ability_value() == 1);
  }
}
