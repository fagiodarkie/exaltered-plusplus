#include "../thirdparty/catch/catch.hpp"
#include "attributes/attributes.h"
#include "attributes/attribute_names.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

TEST_CASE("Attributes")
{
  SECTION("should save attribute in map")
  {
    attribute::attributes sut;
    sut[attribute::attribute_enum::STRENGTH] = TEST_ATTRIBUTE_VALUE;
    REQUIRE(sut[attribute::attribute_enum::STRENGTH] == TEST_ATTRIBUTE_VALUE);
  }

  SECTION("should serialise and deserialise correctly from JSON")
  {
    attribute::attributes stub;
    stub[attribute::attribute_enum::STRENGTH] = TEST_ATTRIBUTE_VALUE;
    attribute::attributes sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut[attribute::attribute_enum::STRENGTH] == TEST_ATTRIBUTE_VALUE);
  }
}
