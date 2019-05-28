#include "../thirdparty/catch/catch.hpp"

#include "abilities/default_ability_factory.h"


TEST_CASE("Default Ability Factory")
{
  character::default_ability_factory sut;
  QList<character::ability_names::ability> abilities_with_variations = { character::ability_names::CRAFT, character::ability_names::MANEUVER };

  SECTION("should retrieve all abilities")
  {
    for (character::ability_names::ability abilityname : character::ability_names::ABILITY_NAME.keys())
      {
        REQUIRE_NOTHROW(sut.get_ability_group(abilityname));
      }
  }

  SECTION("all abilities should have names")
  {
    for (character::ability_names::ability abilityname : character::ability_names::ABILITY_NAME.keys())
      {
        REQUIRE_FALSE(sut.get_ability_group(abilityname).get_name().isEmpty());
      }
  }

  SECTION("simple abilities should not have variations")
  {
    for (character::ability_names::ability abilityname : character::ability_names::ABILITY_NAME.keys())
      {
        if (abilities_with_variations.contains(abilityname))
          continue;

        character::ability_group gut = sut.get_ability_group(abilityname);
        REQUIRE(gut.get_abilities().size() == 1);
        REQUIRE_NOTHROW(gut.get_ability());
        REQUIRE_NOTHROW(gut.get_ability(character::ability_names::ability_declination::NO_DECLINATION));
      }
  }

  SECTION("simple abilities should not have variations")
  {
    for (character::ability_names::ability abilityname : abilities_with_variations)
      {
        character::ability_group gut = sut.get_ability_group(abilityname);
        REQUIRE(gut.get_abilities().size() > 1);
        REQUIRE_THROWS(gut.get_ability());
        REQUIRE_THROWS(gut.get_ability(character::ability_names::ability_declination::NO_DECLINATION));
      }
  }
}
