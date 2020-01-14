#include "../thirdparty/catch/catch.hpp"
#include "attributes/attribute.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

TEST_CASE("Attribute")
{
  SECTION("should create new attribute correctly (name constructor)")
  {
    attribute::attribute sut(TEST_ATTRIBUTE_NAME);
    REQUIRE(TEST_ATTRIBUTE_NAME == sut.get_name());
    REQUIRE(0 == sut);
  }

  SECTION("should create new attribute correctly (name and value constructor)")
  {
    attribute::attribute sut(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
    REQUIRE(TEST_ATTRIBUTE_NAME == sut.get_name());
    REQUIRE(TEST_ATTRIBUTE_VALUE == sut);
  }

  SECTION("should retrieve correctly name and value strings")
  {
    attribute::attribute sut(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
    REQUIRE(sut.get_name() == TEST_ATTRIBUTE_NAME);
    REQUIRE(sut.get_value() == std::to_string(TEST_ATTRIBUTE_VALUE));
  }
}
