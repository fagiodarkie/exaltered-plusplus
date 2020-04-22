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
    sut.add(ability::ability(ability::ability_enum::WAR, 2));
    REQUIRE(sut[ability::ability_enum::WAR].name() == ability::ability_enum::WAR);
    REQUIRE(sut.has(ability::ability_enum::WAR));
    REQUIRE(sut.has(ability::ability_name(ability::ability_enum::WAR)));
  }

  SECTION("should filter by ability type")
  {
    ability::abilities sut;
    sut.add(ability::ability(ability::ability_enum::WAR, 2));
    sut.add(ability::ability(ability::ability_name(ability::ability_enum::WAR, "longterm"), 2));
    sut.add(ability::ability(ability::ability_enum::THROWN, 2));
    sut.add(ability::ability(ability::ability_enum::MEDICINE, 2));
    REQUIRE(sut.size() == 4);
    REQUIRE(sut.with_type(ability::ability_enum::WAR).size() == 2);
  }

  SECTION("should not modify inner abilities if const")
  {
    ability::abilities sut;
    sut.add(ability::ability(ability::ability_enum::WAR, 2));
    const auto csut = sut;
    csut.get(ability::ability_enum::WAR) = 3;
    REQUIRE(csut.get(ability::ability_enum::WAR) == 2);
    csut.get(ability::ability_name(ability::ability_enum::WAR)) = 4;
    REQUIRE(csut.get(ability::ability_enum::WAR) == 2);
  }

  SECTION("should remove an ability by ability name")
  {
    ability::abilities sut;
    sut.add(ability::ability(ability::ability_enum::WAR, 2));
    sut.add(ability::ability(ability::ability_name(ability::ability_enum::WAR, "longterm"), 2));
    sut.add(ability::ability(ability::ability_enum::THROWN, 2));
    sut.add(ability::ability(ability::ability_enum::MEDICINE, 2));

    REQUIRE(sut.size() == 4);
    REQUIRE(sut.has(ability::ability_enum::WAR));
    sut.remove(ability::ability_enum::WAR);
    REQUIRE(sut.size() == 3);
    REQUIRE_FALSE(sut.has(ability::ability_enum::WAR));
    REQUIRE(sut.has(ability::ability_name(ability::ability_enum::WAR, "longterm")));

    sut.remove(ability::ability_enum::MELEE_LIGHT);
    REQUIRE(sut.size() == 3);

    sut.remove(ability::ability_name(ability::ability_enum::WAR, "longterm"));
    REQUIRE_FALSE(sut.has(ability::ability_name(ability::ability_enum::WAR, "longterm")));
  }

  SECTION("should retrieve ability keys")
  {
    ability::abilities sut;
    sut.add(ability::ability(ability::ability_enum::WAR, 2));
    sut.add(ability::ability(ability::ability_name(ability::ability_enum::WAR, "longterm"), 2));
    sut.add(ability::ability(ability::ability_enum::THROWN, 2));
    sut.add(ability::ability(ability::ability_enum::MEDICINE, 2));

    auto res = sut.keys();
    REQUIRE(res.size() == 4);
    REQUIRE(std::find(res.begin(), res.end(), ability::ability_enum::WAR) != res.end());
    REQUIRE(std::find(res.begin(), res.end(), ability::ability_enum::THROWN) != res.end());
    REQUIRE(std::find(res.begin(), res.end(), ability::ability_enum::MEDICINE) != res.end());
    REQUIRE(std::find(res.begin(), res.end(), ability::ability_name(ability::ability_enum::WAR, "longterm")) != res.end());
    REQUIRE(std::find(res.begin(), res.end(), ability::ability_enum::MELEE_LIGHT) == res.end());
  }

  SECTION("should create correctly from JSON")
  {
    ability::abilities stub;
    ability::ability ability(ability::ability_enum::WAR, TEST_ABILITY_VALUE);
    ability.add("spec", 1);
    stub[ability::ability_enum::WAR] = ability;

    ability::abilities sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut[ability::ability_enum::WAR].name().name() == "Strategy");
    REQUIRE(sut[ability::ability_enum::WAR].specialisations().size() == 1);
  }
}
