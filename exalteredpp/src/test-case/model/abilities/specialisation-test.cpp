#include "../thirdparty/catch/catch.hpp"
#include "abilities/specialisation.h"

#define TEST_SPEC_NAME "test-spec"
#define TEST_SPEC_VALUE 1

TEST_CASE("Specialisation")
{
  SECTION("should create new specialisation correctly (name constructor)")
  {
    ability::specialisation sut(TEST_SPEC_NAME);
    REQUIRE(sut.name() == TEST_SPEC_NAME);
    REQUIRE(sut.value() == TEST_SPEC_VALUE);
  }

  SECTION("should create new specialisation correctly (name and value constructor)")
  {
    ability::specialisation sut(TEST_SPEC_NAME, TEST_SPEC_VALUE);
    REQUIRE(sut.name() == TEST_SPEC_NAME);
    REQUIRE(sut.value() == TEST_SPEC_VALUE);
  }

  SECTION("should retrieve correctly name and value strings")
  {
    ability::specialisation sut(TEST_SPEC_NAME, TEST_SPEC_VALUE);
    REQUIRE((std::string)sut == TEST_SPEC_NAME);
  }

  SECTION("should compare equal with an specialisation with same name and value")
  {
    ability::specialisation sut(TEST_SPEC_NAME, TEST_SPEC_VALUE), other(TEST_SPEC_NAME, TEST_SPEC_VALUE);
    REQUIRE(sut == other);
    other.set_value(TEST_SPEC_VALUE + 1);
    REQUIRE_FALSE(sut == other);
  }

  SECTION("should create correctly via JSON Object")
  {
    ability::specialisation stub(TEST_SPEC_NAME, TEST_SPEC_VALUE);

    ability::specialisation sut("");
    sut.deserialise(stub.serialise());

    REQUIRE(sut.name() == stub.name());
    REQUIRE(sut.value() == stub.value());
  }

  SECTION("should create correctly via constructors")
  {
    ability::specialisation stub(TEST_SPEC_NAME, TEST_SPEC_VALUE);

    ability::specialisation sut_1(stub), sut_2("a");
    sut_2 = stub;

    REQUIRE(sut_1.name() == stub.name());
    REQUIRE(sut_1.value() == stub.value());
    REQUIRE(sut_2.name() == stub.name());
    REQUIRE(sut_2.value() == stub.value());
  }

  SECTION("should increase when told to")
  {
    ability::specialisation sut(TEST_SPEC_NAME, 0);
    REQUIRE(sut == 0);
    sut += 1;
    REQUIRE(sut == 1);
    sut.increase(2);
    REQUIRE(sut == 3);
  }
}
