#include "../thirdparty/catch/catch.hpp"
#include "abilities/specialisation.h"

#define TEST_SPEC_NAME "test-spec"
#define TEST_SPEC_VALUE 1

TEST_CASE("Specialisation")
{
  SECTION("should create new specialisation correctly (name constructor)")
  {
    character::specialisation sut(TEST_SPEC_NAME);
    REQUIRE(sut.get_name() == TEST_SPEC_NAME);
    REQUIRE(sut.get_specialisation_value() == TEST_SPEC_VALUE);
    REQUIRE(sut.get_value() == "1");
  }

  SECTION("should create new specialisation correctly (name and value constructor)")
  {
    character::specialisation sut(TEST_SPEC_NAME, TEST_SPEC_VALUE);
    REQUIRE(sut.get_name() == TEST_SPEC_NAME);
    REQUIRE(sut.get_specialisation_value() == TEST_SPEC_VALUE);
    REQUIRE(sut.get_value() == "1");
  }

  SECTION("should retrieve correctly name and value strings")
  {
    character::specialisation sut(TEST_SPEC_NAME, TEST_SPEC_VALUE);
    REQUIRE(sut.get_name() == TEST_SPEC_NAME);
    REQUIRE(sut.get_value() == QString::number(TEST_SPEC_VALUE));
  }

  SECTION("should compare equal with an specialisation with same name and value")
  {
    character::specialisation sut(TEST_SPEC_NAME, TEST_SPEC_VALUE), other(TEST_SPEC_NAME, TEST_SPEC_VALUE);
    REQUIRE(sut == other);
    other.set_value(TEST_SPEC_VALUE + 1);
    REQUIRE_FALSE(sut == other);
  }

  SECTION("should create correctly via JSON Object")
  {
    character::specialisation stub(TEST_SPEC_NAME, TEST_SPEC_VALUE);

    QJsonObject obj;
    stub.write_to_json(obj);

    character::specialisation sut("");
    sut.read_from_json(obj);

    REQUIRE(sut.get_name() == stub.get_name());
    REQUIRE(sut.get_specialisation_value() == stub.get_specialisation_value());
  }

  SECTION("should create correctly via JSON Object")
  {
    character::specialisation stub(TEST_SPEC_NAME, TEST_SPEC_VALUE);

    character::specialisation sut = stub;

    REQUIRE(sut.get_name() == stub.get_name());
    REQUIRE(sut.get_specialisation_value() == stub.get_specialisation_value());
  }
}