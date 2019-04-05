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
    REQUIRE(sut.get_ability("a1").get_ability_value() == 1);
    REQUIRE(sut.get_ability("a1").get_value() == "1");
    REQUIRE(sut.get_ability("a2").get_ability_value() == 2);
    REQUIRE(sut.get_ability("a2").get_value() == "2");
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

  SECTION("should not prevent new ability if it has ability declinations")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    REQUIRE_NOTHROW(sut.add_ability("a3"));
    REQUIRE(sut.get_ability("a3").get_name() == "a3");
  }

  SECTION("should prevent new ability if it is simple")
  {
    ability_group sut(ABILITYNAME);
    REQUIRE_THROWS(sut.add_ability("a1"));
    REQUIRE_FALSE(sut.has_ability("a1"));
    REQUIRE_THROWS(sut.get_ability("a1"));
  }

  SECTION("should not change specialisation names")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    ability_group sut_simple(ABILITYNAME);
    sut_simple.add_specialisation(specialisation("s1"));
    REQUIRE(sut.get_specialisations().at(0).get_name() == "s1");
    REQUIRE(sut_simple.get_specialisations().at(0).get_name() == "s1");
  }

  SECTION("should throw if specialisation doesn't exist")
  {
    ability_group sut(ABILITYNAME);
    REQUIRE_FALSE(sut.has_specialisation("doesn't exist"));
    REQUIRE_THROWS(sut.get_specialisation("doesn't exist"));
  }

  SECTION("should keep specialisation value")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    REQUIRE(sut.get_specialisations().size() == 1);
    REQUIRE(sut.has_specialisation("s1"));
    REQUIRE(sut.get_specialisation("s1").get_value() == "3");
    REQUIRE(sut.get_specialisation("s1").get_name() == "s1");
    REQUIRE(sut.get_specialisation("s1").get_specialisation_value() == 3);
  }

  SECTION("should allow new ability and specialisation generation with name / value pairs")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    sut.add_ability("a3", 1);
    sut.add_specialisation("s2", 2);
    REQUIRE(sut.has_ability("a3"));
    REQUIRE(sut.has_specialisation("s2"));
  }

  SECTION("should allow to modify ability values")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    sut.set_ability_value("a1", 0);
    REQUIRE(sut.get_ability("a1") == 0);
    sut.increase_ability_value("a1");
    REQUIRE(sut.get_ability("a1") == 1);
    sut.increase_ability_value("a1", 2);
    REQUIRE(sut.get_ability("a1") == 3);
    sut.add_ability(ability("a3", 4));
    REQUIRE(sut.get_ability("a3") == 4);
  }

  SECTION("should throw if trying to update a non-existing ability")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    REQUIRE_THROWS(sut.set_ability_value("a3", 4));
  }

  SECTION("should allow to modify specialisation values")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    sut.set_specialisation_value("s1", 0);
    REQUIRE(sut.get_specialisation("s1").get_specialisation_value() == 0);
    sut.increase_specialisation_value("s1");
    REQUIRE(sut.get_specialisation("s1").get_specialisation_value() == 1);
    sut.increase_specialisation_value("s1", 2);
    REQUIRE(sut.get_specialisation("s1").get_specialisation_value() == 3);
  }

  SECTION("should allow to remove specialisation")
  {
    ability_group sut(ABILITYNAME, { ability("a1", 1), ability("a2", 2) }, {specialisation("s1", 3)});
    REQUIRE_NOTHROW(sut.remove_specialisation("s2"));
    REQUIRE(sut.get_specialisations().count() == 1);
    REQUIRE_NOTHROW(sut.remove_specialisation("s1"));
    REQUIRE(sut.get_specialisations().count() == 0);
  }
}
