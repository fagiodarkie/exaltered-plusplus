#include "../catch/catch.hpp"
#include "attributes.h"

#define TEST_ATTRIBUTE_NAME "test-attribute"
#define TEST_ATTRIBUTE_VALUE 1

using character::attribute;
using std::string;

TEST_CASE("Attributes")
{
	SECTION("should create new attribute correctly (name constructor)")
	{
		attribute sut(TEST_ATTRIBUTE_NAME);
		REQUIRE((string)sut == string(TEST_ATTRIBUTE_NAME));
		REQUIRE((int)sut == 0);
	}

	SECTION("should create new attribute correctly (name and value constructor)")
	{
		attribute sut(TEST_ATTRIBUTE_NAME, TEST_ATTRIBUTE_VALUE);
		REQUIRE((string)sut == string(TEST_ATTRIBUTE_NAME));
		REQUIRE((int)sut == TEST_ATTRIBUTE_VALUE);
	}
}