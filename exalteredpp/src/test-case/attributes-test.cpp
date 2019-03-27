#include "../thirdparty/catch/catch.hpp"
#include "attributes/attributes.h"
#include "attributes/attribute_names.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

TEST_CASE("Attributes")
{
  SECTION("should save attribute in map")
  {
    character::attribute attribute(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
    character::attributes sut;
    sut.insert(character::attribute_name::STRENGTH, attribute);
    REQUIRE(int(sut.value(character::attribute_name::STRENGTH)) == TEST_ATTRIBUTE_VALUE);
    REQUIRE(QString(sut.value(character::attribute_name::STRENGTH)) == QString(TEST_ATTRIBUTE_NAME));
  }
}
