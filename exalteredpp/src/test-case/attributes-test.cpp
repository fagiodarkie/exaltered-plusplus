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

  SECTION("should create correctly from JSON")
  {
    QJsonObject from;
    from[character::ATTRIBUTE_NAME.value(character::attribute_name::STRENGTH)] = TEST_ATTRIBUTE_VALUE;
    character::attributes sut;
    sut.read_from_json(from);
    REQUIRE(sut.value(character::attribute_name::STRENGTH) == TEST_ATTRIBUTE_VALUE);
  }

  SECTION("should write correctly to JSON")
  {
    character::attributes sut;
    sut.insert(character::attribute_name::STRENGTH, character::attribute(character::ATTRIBUTE_NAME.value(character::attribute_name::STRENGTH), TEST_ATTRIBUTE_VALUE));
    QJsonObject from;
    sut.write_to_json(from);
    REQUIRE(from[character::ATTRIBUTE_NAME.value(character::attribute_name::STRENGTH)].toInt() == TEST_ATTRIBUTE_VALUE);
  }
}
