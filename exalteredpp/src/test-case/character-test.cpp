#include "../thirdparty/catch/catch.hpp"
#include "character/attributes/attribute.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

using character::attribute;

TEST_CASE("Character")
{
	SECTION("should create new attribute correctly (name constructor)")
	{
		attribute sut(TEST_ATTRIBUTE_NAME);
	REQUIRE(QString(TEST_ATTRIBUTE_NAME) == QString(sut));
	REQUIRE(0 == int(sut));
    }

	SECTION("should create new attribute correctly (name and value constructor)")
	{
		attribute sut(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
	REQUIRE(QString(TEST_ATTRIBUTE_NAME) == QString(sut));
	REQUIRE(TEST_ATTRIBUTE_VALUE == int(sut));
	}
}
