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

  SECTION("should update its value")
  {
    ability::ability sut(ability::WAR, 1);
    sut.set_value(2);
    REQUIRE(sut == 2);
    sut += 4;
    REQUIRE(sut == 6);
    sut -= 3;
    REQUIRE(sut == 3);
    ++sut;
    REQUIRE(sut == 4);
    --sut;
    REQUIRE(sut == 3);
  }

  SECTION("should manage its name as an ability_name")
  {
    ability::ability sut(ability::WAR, 1);
    REQUIRE((ability::ability_name)sut == ability::WAR);
  }

  SECTION("should manage its name as a string")
  {
    ability::ability sut(ability::WAR, 1);
    REQUIRE(sut.name().name() == (std::string)sut);
  }

  SECTION("should manage its specialisations")
  {
    ability::ability sut(ability::WAR, 1);
    REQUIRE(sut.specialisations().size() == 0);
    sut.set("strategy", 1);
    REQUIRE(sut.specialisations().size() == 1);
    REQUIRE(sut.get("strategy") == 1);
    REQUIRE(sut[std::string("strategy")] == 2);
    sut.increase("strategy");
    REQUIRE(sut.get("strategy") == 2);
    REQUIRE(sut[std::string("strategy")] == 3);
    sut.increase("strategy", 2);
    REQUIRE(sut.get("strategy") == 4);

    sut.remove("strategy");
    REQUIRE(sut.specialisations().size() == 0);
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
