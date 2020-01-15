#include "../thirdparty/catch/catch.hpp"
#include "abilities/ability.h"

#define TEST_ABILITY_NAME "test-attribute"
#define TEST_ABILITY_VALUE 1

TEST_CASE("Ability")
{
  SECTION("should create new ability correctly (name constructor)")
  {
    ability::ability sut(TEST_ABILITY_NAME);
    REQUIRE(sut.name() == TEST_ABILITY_NAME);
    REQUIRE(0 == sut);
  }

  SECTION("should create new ability correctly (name and value constructor)")
  {
    ability::ability sut(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    REQUIRE(TEST_ABILITY_NAME == sut.name());
    REQUIRE(TEST_ABILITY_VALUE == sut);
  }

  SECTION("should retrieve correctly name and value strings")
  {
    ability::ability sut(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    REQUIRE(sut.name() == TEST_ABILITY_NAME);
  }

  SECTION("should compare equal with an ability with same name and value")
  {
    ability::ability sut(TEST_ABILITY_NAME, TEST_ABILITY_VALUE), other(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    REQUIRE(sut == other);
    other.set_value(TEST_ABILITY_VALUE + 1);
    REQUIRE_FALSE(sut == other);
  }

  SECTION("should save and load QJsonObject")
  {
    ability::ability stub(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);
    ability::ability sut;
    sut.deserialise(stub.serialise());

    REQUIRE(stub.name() == sut.name());
    REQUIRE(stub.get_ability_value() == sut.get_ability_value());
  }

  SECTION("should create same object when using assignment operator")
  {
    ability::ability stub(TEST_ABILITY_NAME, TEST_ABILITY_VALUE);

    ability::ability sut_1(stub), sut_2;
    sut_2 = stub;

    REQUIRE(stub.name() == sut_1.name());
    REQUIRE(stub.get_ability_value() == sut_1.get_ability_value());
    REQUIRE(stub.name() == sut_2.name());
    REQUIRE(stub.get_ability_value() == sut_2.get_ability_value());
  }
}
