#include "../thirdparty/catch/catch.hpp"

#include "abilities/ability_group.h"

#define ABILITYNAME "ability-name"

using namespace character;

TEST_CASE("Ability group")
{
  SECTION("should create simple ability by default")
  {
    ability_group sut(ABILITYNAME);
    REQUIRE(sut.has_ability(ability_declination::NO_DECLINATION));
    REQUIRE_FALSE(sut.has_abilities());
  }

  SECTION("if created with default declination, should be seen as simple")
  {
    ability_group sut(ABILITYNAME, {ability(ability_declination::NO_DECLINATION)});
    REQUIRE(sut.has_ability(ability_declination::NO_DECLINATION));
    REQUIRE_FALSE(sut.has_abilities());
  }

  SECTION("should consider ability declinations and specialisations if requested")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    REQUIRE_FALSE(sut.has_ability(ability_declination::NO_DECLINATION));
    REQUIRE(sut.has_abilities());

    REQUIRE_THROWS(sut.get_ability());
  }

  SECTION("should keep right values of abilities")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
  }

  SECTION("should change ability names if it has ability declinations")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    REQUIRE(sut.get_abilities().at(0).get_name() == QString(ABILITYNAME) + " (a1)");
    REQUIRE(sut.get_abilities().at(1).get_name() == QString(ABILITYNAME) + " (a2)");
  }

  SECTION("should not change ability names if it is simple")
  {
    ability_group sut(ABILITYNAME);
    REQUIRE(sut.get_abilities().at(0).get_name() == ABILITYNAME);
  }

  SECTION("should not change specialisation names")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    ability_group sut_simple(ABILITYNAME);
    sut_simple.add_specialisation(specialisation("s1"));
    REQUIRE(sut.get_specialisations().at(0).get_name() == "s1");
    REQUIRE(sut_simple.get_specialisations().at(0).get_name() == "s1");
  }
}
