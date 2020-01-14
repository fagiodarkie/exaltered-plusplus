#include "../thirdparty/catch/catch.hpp"
#include "attributes/attributes.h"
#include "attributes/attribute_names.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

TEST_CASE("Attributes")
{
  SECTION("should save attribute in map")
  {
    attribute::attribute attribute(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
    attribute::attributes sut;
    sut[attribute::STRENGTH] = attribute;
    REQUIRE(sut[attribute::STRENGTH] == TEST_ATTRIBUTE_VALUE);
    REQUIRE(sut[attribute::STRENGTH].get_name() == std::string(TEST_ATTRIBUTE_NAME));
  }

  SECTION("should serialise and deserialise correctly from JSON")
  {
    attribute::attributes stub;
    stub[attribute::STRENGTH] = attribute::attribute(attribute::ATTRIBUTE_NAME.at(attribute::STRENGTH), TEST_ATTRIBUTE_VALUE);
    attribute::attributes sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut[attribute::STRENGTH] == TEST_ATTRIBUTE_VALUE);
  }
}
