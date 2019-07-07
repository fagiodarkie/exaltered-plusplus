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
    sut.insert(attribute::STRENGTH, attribute);
    REQUIRE(int(sut.value(attribute::STRENGTH)) == TEST_ATTRIBUTE_VALUE);
    REQUIRE(QString(sut.value(attribute::STRENGTH)) == QString(TEST_ATTRIBUTE_NAME));
  }

  SECTION("should create correctly from JSON")
  {
    QJsonObject from;
    from[ATTRIBUTE_NAME.value(attribute::STRENGTH)] = TEST_ATTRIBUTE_VALUE;
    character::attributes sut;
    sut.read_from_json(from);
    REQUIRE(sut.value(attribute::STRENGTH) == TEST_ATTRIBUTE_VALUE);
  }

  SECTION("should write correctly to JSON")
  {
    character::attributes sut;
    sut.insert(attribute::STRENGTH, character::attribute(ATTRIBUTE_NAME.value(attribute::STRENGTH), TEST_ATTRIBUTE_VALUE));
    QJsonObject from;
    sut.write_to_json(from);
    REQUIRE(from[ATTRIBUTE_NAME.value(attribute::STRENGTH)].toInt() == TEST_ATTRIBUTE_VALUE);
  }
}
