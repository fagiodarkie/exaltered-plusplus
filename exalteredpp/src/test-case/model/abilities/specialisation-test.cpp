#include "../thirdparty/catch/catch.hpp"
#include "abilities/specialisation.h"

#define TEST_SPEC_NAME "test-spec"
#define TEST_SPEC_VALUE 1

TEST_CASE("Specialisation")
{
  SECTION("should create new specialisation correctly (name constructor)")
  {
    ability::specialisation sut(TEST_SPEC_NAME);
    REQUIRE(sut.get_name() == TEST_SPEC_NAME);
    REQUIRE(sut.get_specialisation_value() == TEST_SPEC_VALUE);
    REQUIRE(sut.get_value() == "1");
  }

  SECTION("should create new specialisation correctly (name and value constructor)")
  {
    ability::specialisation sut(TEST_SPEC_NAME, TEST_SPEC_VALUE);
    REQUIRE(sut.get_name() == TEST_SPEC_NAME);
    REQUIRE(sut.get_specialisation_value() == TEST_SPEC_VALUE);
    REQUIRE(sut.get_value() == "1");
  }

  SECTION("should retrieve correctly name and value strings")
  {
    ability::specialisation sut(TEST_SPEC_NAME, TEST_SPEC_VALUE);
    REQUIRE(sut.get_name() == TEST_SPEC_NAME);
    REQUIRE(sut.get_value() == std::to_string(TEST_SPEC_VALUE));
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

    REQUIRE(sut.get_name() == stub.get_name());
    REQUIRE(sut.get_specialisation_value() == stub.get_specialisation_value());
  }

  SECTION("should create correctly via JSON Object")
  {
    ability::specialisation stub(TEST_SPEC_NAME, TEST_SPEC_VALUE);

    ability::specialisation sut_1(stub), sut_2("a");
    sut_2 = stub;

    REQUIRE(sut_1.get_name() == stub.get_name());
    REQUIRE(sut_1.get_specialisation_value() == stub.get_specialisation_value());
    REQUIRE(sut_2.get_name() == stub.get_name());
    REQUIRE(sut_2.get_specialisation_value() == stub.get_specialisation_value());
  }
}
