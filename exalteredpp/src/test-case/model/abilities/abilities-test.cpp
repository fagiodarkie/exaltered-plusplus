#include "../thirdparty/catch/catch.hpp"
#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "json_constants.h"

#include <QJsonArray>

#define TEST_ABILITY_NAME "test-ability"
#define TEST_ABILITY_VALUE 1

TEST_CASE("Abilities")
{

  SECTION("should save ability in map")
  {
    ability::abilities sut;
    sut.add(ability::ability(ability::WAR, 2));
    REQUIRE(sut[ability::WAR].name() == ability::WAR);
    REQUIRE(sut.has(ability::WAR));
    REQUIRE(sut.has(ability::ability_name(ability::WAR)));
  }

  SECTION("should filter by ability type")
  {
    ability::abilities sut;
    sut.add(ability::ability(ability::WAR, 2));
    sut.add(ability::ability(ability::ability_name(ability::WAR, "longterm"), 2));
    sut.add(ability::ability(ability::TEACHING, 2));
    sut.add(ability::ability(ability::MEDICINE, 2));
    REQUIRE(sut.size() == 4);
    REQUIRE(sut.with_type(ability::WAR).size() == 2);
  }

  SECTION("should not modify inner abilities if const")
  {
    ability::abilities sut;
    sut.add(ability::ability(ability::WAR, 2));
    const auto csut = sut;
    csut.get(ability::WAR) = 3;
    REQUIRE(csut.get(ability::WAR) == 2);
    csut.get(ability::ability_name(ability::WAR)) = 4;
    REQUIRE(csut.get(ability::WAR) == 2);
  }

  SECTION("should remove an ability by ability name")
  {
    ability::abilities sut;
    sut.add(ability::ability(ability::WAR, 2));
    sut.add(ability::ability(ability::ability_name(ability::WAR, "longterm"), 2));
    sut.add(ability::ability(ability::TEACHING, 2));
    sut.add(ability::ability(ability::MEDICINE, 2));

    REQUIRE(sut.size() == 4);
    REQUIRE(sut.has(ability::WAR));
    sut.remove(ability::WAR);
    REQUIRE(sut.size() == 3);
    REQUIRE_FALSE(sut.has(ability::WAR));
    REQUIRE(sut.has(ability::ability_name(ability::WAR, "longterm")));

    sut.remove(ability::MELEE);
    REQUIRE(sut.size() == 3);

    sut.remove(ability::ability_name(ability::WAR, "longterm"));
    REQUIRE_FALSE(sut.has(ability::ability_name(ability::WAR, "longterm")));
  }

  SECTION("should create correctly from JSON")
  {
    ability::abilities stub;
    ability::ability ability(ability::WAR, TEST_ABILITY_VALUE);
    ability.add("spec", 1);
    stub[ability::WAR] = ability;

    ability::abilities sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut[ability::WAR].name().name() == "War");
    REQUIRE(sut[ability::WAR].specialisations().size() == 1);
  }
}
