#include "../thirdparty/catch/catch.hpp"
#include "abilities/ability.h"

#define TEST_ABILITY_NAME "test-attribute"
#define TEST_ABILITY_VALUE 1

TEST_CASE("Ability")
{
  SECTION("should create new attribute correctly (name constructor)")
  {
    character::ability sut(TEST_ABILITY_NAME);
    REQUIRE(QString(TEST_ABILITY_NAME) == QString(sut));
    REQUIRE(0 == int(sut));
  }

  SECTION("should create new attribute correctly (name and value constructor)")
  {
    character::ability sut(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    REQUIRE(QString(TEST_ABILITY_NAME) == QString(sut));
    REQUIRE(TEST_ABILITY_VALUE == int(sut));
  }

  SECTION("should retrieve correctly name and value strings")
  {
    character::ability sut(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    REQUIRE(sut.get_name() == TEST_ABILITY_NAME);
    REQUIRE(sut.get_value() == QString::number(TEST_ABILITY_VALUE));
  }
}
