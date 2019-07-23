#include "../thirdparty/catch/catch.hpp"
#include "social/philosophy.h"

TEST_CASE("philosophy")
{
  SECTION("should create correctly with constructor")
  {
    character::social::philosophy sut("name", 2);

    REQUIRE(sut.name() == "name");
    REQUIRE(sut.value() == 2);
  }

  SECTION("should read and write correctly in JSON object")
  {
    character::social::philosophy stub("name", 3);

    character::social::philosophy sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut.name() == stub.name());
    REQUIRE(sut.value() == stub.value());
    REQUIRE(sut == stub);
  }

  SECTION("should assign new value")
  {
    character::social::philosophy sut("name", 3);
    REQUIRE(sut.value() == 3);
    sut.set_value(2);
    REQUIRE(sut.value() == 2);
  }
}
