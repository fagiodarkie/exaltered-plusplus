#include "../thirdparty/catch/catch.hpp"
#include "abilities/abilities.h"
#include "abilities/ability.h"

#define TEST_ABILITY_NAME "test-attribute"
#define TEST_ABILITY_VALUE 1

TEST_CASE("Abilities")
{
  SECTION("should save ability in map")
  {
    character::ability ability(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    character::abilities sut;
    sut.insert(character::ability_name::WAR, ability);
    REQUIRE(int(sut.value(character::ability_name::WAR)) == TEST_ABILITY_VALUE);
    REQUIRE(QString(sut.value(character::ability_name::WAR)) == QString(TEST_ABILITY_NAME));
  }

  SECTION("should create correctly from JSON")
  {
    QJsonObject from;
    from[character::ABILITY_NAME.value(character::ability_name::WAR)] = TEST_ABILITY_VALUE;
    character::abilities sut;
    sut.read(from);
    REQUIRE(sut.value(character::ability_name::WAR) == TEST_ABILITY_VALUE);
  }

  SECTION("should write correctly to JSON")
  {
    character::abilities sut;
    sut.insert(character::ability_name::WAR, character::ability(character::ABILITY_NAME.value(character::ability_name::WAR), TEST_ABILITY_VALUE));
    QJsonObject from;
    sut.write(from);
    REQUIRE(from[character::ABILITY_NAME.value(character::ability_name::WAR)].toInt() == TEST_ABILITY_VALUE);
  }
}
