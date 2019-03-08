#include "../thirdparty/catch/catch.hpp"
#include "character/attributes/attributes.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

using character::attribute;
using std::string;

TEST_CASE("Attributes")
{
	SECTION("should create new attribute correctly (name constructor)")
	{
		attribute sut(TEST_ATTRIBUTE_NAME);
        REQUIRE(string(TEST_ATTRIBUTE_NAME) == string(sut));
        REQUIRE(0 == int(sut));
    }

	SECTION("should create new attribute correctly (name and value constructor)")
	{
		attribute sut(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
        REQUIRE(string(TEST_ATTRIBUTE_NAME) == string(sut));
        REQUIRE(TEST_ATTRIBUTE_VALUE == int(sut));
	}
}
