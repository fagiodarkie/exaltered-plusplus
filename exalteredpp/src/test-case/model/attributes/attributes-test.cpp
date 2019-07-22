#include "../thirdparty/catch/catch.hpp"
#include "attributes/attributes.h"
#include "attributes/attribute_names.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

using namespace character::attribute_names;

TEST_CASE("Attributes")
{
  SECTION("should save attribute in map")
  {
    character::attribute attribute(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
    character::attributes sut;
    sut[STRENGTH] = attribute;
    REQUIRE(sut[STRENGTH] == TEST_ATTRIBUTE_VALUE);
    REQUIRE(sut[STRENGTH].get_name() == std::string(TEST_ATTRIBUTE_NAME));
  }

  SECTION("should serialise and deserialise correctly from JSON")
  {
    character::attributes stub;
    stub[STRENGTH] = character::attribute(ATTRIBUTE_NAME.at(STRENGTH), TEST_ATTRIBUTE_VALUE);
    character::attributes sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut[STRENGTH] == TEST_ATTRIBUTE_VALUE);
  }
}
