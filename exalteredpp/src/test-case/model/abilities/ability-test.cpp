#include "../thirdparty/catch/catch.hpp"
#include "abilities/ability.h"

TEST_CASE("Ability")
{
  SECTION("should create new ability correctly (name constructor)")
  {
    ability::ability sut(ability::WAR);
    REQUIRE(sut.name().ability_type == ability::WAR);
    REQUIRE(0 == (int)sut);
  }

  SECTION("should create new ability correctly (name and value constructor)")
  {
    ability::ability sut(ability::WAR, 1);
    REQUIRE(sut.name().name() == "War");
    REQUIRE(1 == (int)sut);
  }

  SECTION("should compare equal with an ability with same name and value")
  {
    ability::ability sut(ability::WAR, 1), other(ability::WAR, 1);
    REQUIRE(sut == other);
    ++other;
    REQUIRE_FALSE(sut == other);
  }

  SECTION("should save and load QJsonObject")
  {
    ability::ability stub(ability::WAR, 1);
    ability::ability sut;
    sut.deserialise(stub.serialise());

    REQUIRE(stub.name() == sut.name());
    REQUIRE(stub.value() == sut.value());
  }

  SECTION("should create same object when using assignment operator")
  {
    ability::ability stub(ability::WAR, 1);

    ability::ability sut_1(stub), sut_2;
    sut_2 = stub;

    REQUIRE(stub.name() == sut_1.name());
    REQUIRE(stub.value() == sut_1.value());
    REQUIRE(stub.name() == sut_2.name());
    REQUIRE(stub.value() == sut_2.value());
  }
}
