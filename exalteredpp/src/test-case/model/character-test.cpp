#include "../thirdparty/catch/catch.hpp"
#include "character/character.h"
#include "serialisation/json_constants.h"

#define CHARACTER_NAME "test-name"
#define TEST_ATTRIBUTE_NAME "test-attribute"
#define STANDARD_CHARACTER character::character(CHARACTER_NAME, character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, attribute::attributes(), ability::abilities(), virtues::virtues(), power::power_container())

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
    sut.set_attribute(attribute::STRENGTH, attribute::attribute(TEST_ATTRIBUTE_NAME));
    attribute::attribute saved_attribute = sut.get_attribute(attribute::STRENGTH);
    REQUIRE(saved_attribute.get_name() == TEST_ATTRIBUTE_NAME);
  }

  SECTION("should accept a new ability group")
  {
    character::character sut = STANDARD_CHARACTER;
    sut.set_ability(ability::WAR, ability::ability_group());
    ability::ability_group saved_ability = sut.get_ability_group(ability::WAR);
    REQUIRE(saved_ability.get_name() == "War");
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
    sut.set_ability(ability::CRAFT, ability::ability_group(ability::CRAFT, { ability::ability("new_ability", 1) }));
    sut.set_ability(ability::WAR, ability::ability_group(ability::WAR));
    sut.set_ability_value(ability::MELEE, 5);
    REQUIRE(sut.get_ability_group(ability::WAR).get_name() == "War");
    REQUIRE(sut.get_ability(ability::WAR).get_name() == ability::ability_declination::NO_DECLINATION);
    REQUIRE(sut.get_ability(ability::WAR).get_ability_value() == 0);
    REQUIRE(sut.get_ability(ability::CRAFT, "new_ability").get_name() == "new_ability");
    REQUIRE(sut.get_ability(ability::CRAFT, "new_ability").get_ability_value() == 1);
    REQUIRE(sut.get_ability(ability::MELEE).get_ability_value() == 5);
  }

  SECTION("should retrieve caste correctly")
  {
    character::character sut = STANDARD_CHARACTER;
    REQUIRE(sut.caste() == character::exalt::caste::NO_CASTE);
  }

  SECTION("should allow virtue & vice management")
  {
    character::character sut = STANDARD_CHARACTER;

    sut.set_vice(  virtues::vice_enum::ENVY, 3);
    sut.get_virtue(virtues::virtue_enum::VALOR       ).set_value(1);
    sut.get_virtue(virtues::virtue_enum::COMPASSION  ).set_value(2);
    sut.get_virtue(virtues::virtue_enum::TEMPERANCE  ).set_value(3);
    sut.get_virtue(virtues::virtue_enum::CONVINCTION ).set_value(4);

    REQUIRE(sut.get_vice() == virtues::vice_enum::ENVY);
    REQUIRE(sut.get_vice_value() == 3);
    REQUIRE(sut.get_virtue(virtues::virtue_enum::VALOR       ).value() == 1);
    REQUIRE(sut.get_virtue(virtues::virtue_enum::COMPASSION  ).value() == 2);
    REQUIRE(sut.get_virtue(virtues::virtue_enum::TEMPERANCE  ).value() == 3);
    REQUIRE(sut.get_virtue(virtues::virtue_enum::CONVINCTION ).value() == 4);
  }

  SECTION("should allow direct access to health, willpower, essence and logos")
  {
    character::character sut = STANDARD_CHARACTER;

    sut.get_logos().set_logos(2);
    sut.get_essence().set_permanent_essence(5);
    sut.get_willpower().set_permanent_willpower(3);
    sut.get_health().set_total_health(100);

    REQUIRE(sut.get_logos()     .get_logos()           == 2  );
    REQUIRE(sut.get_essence()   .permanent_essence()   == 5  );
    REQUIRE(sut.get_willpower() .permanent_willpower() == 3  );
    REQUIRE(sut.get_health()    .total_health()        == 100);

    const character::character c_sut = STANDARD_CHARACTER;

    c_sut.get_logos().set_logos(2);
    c_sut.get_essence().set_permanent_essence(5);
    c_sut.get_willpower().set_permanent_willpower(3);
    c_sut.get_health().set_total_health(100);

    REQUIRE_FALSE(c_sut.get_logos()     .get_logos()           == 2  );
    REQUIRE_FALSE(c_sut.get_essence()   .permanent_essence()   == 5  );
    REQUIRE_FALSE(c_sut.get_willpower() .permanent_willpower() == 3  );
    REQUIRE_FALSE(c_sut.get_health()    .total_health()        == 100);

  }
}
