#include "../thirdparty/catch/catch.hpp"
#include "character/attributes/attributes.h"
#include "character/attributes/attribute_names.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

TEST_CASE("Attributes")
{
  SECTION("should save attribute in map")
  {
    character::attribute attribute(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
    character::attributes sut;
    sut.emplace(character::attribute_name::STRENGTH, attribute);
    REQUIRE(int(sut.at(character::attribute_name::STRENGTH)) == TEST_ATTRIBUTE_VALUE);
    REQUIRE(QString(sut.at(character::attribute_name::STRENGTH)) == QString(TEST_ATTRIBUTE_NAME));
  }
}
