#include "../thirdparty/catch/catch.hpp"
#include "power/willpower.h"

TEST_CASE("willpower")
{
  SECTION("should create correctly")
  {
    power::willpower sut(10, 8);

    REQUIRE(sut.permanent_willpower() == 10);
    REQUIRE(sut.temporary_willpower() == 8);
  }

  SECTION("should consume and restore willpower correctly")
  {
    power::willpower sut(10, 8);

    REQUIRE(sut.can_consume(3));
    REQUIRE(sut.can_consume(8));
    REQUIRE_FALSE(sut.can_consume(10));

    sut.consume(5);
    REQUIRE(sut.temporary_willpower() == 3);
    REQUIRE(sut.can_consume(3));
    REQUIRE_FALSE(sut.can_consume(8));

    sut.consume(5);
    REQUIRE(sut.temporary_willpower() == 0);
    REQUIRE_FALSE(sut.can_consume(3));

    sut.restore(5);
    REQUIRE(sut.temporary_willpower() == 5);
    REQUIRE(sut.can_consume(3));
    REQUIRE_FALSE(sut.can_consume(8));

    sut.restore(5);
    REQUIRE(sut.temporary_willpower() == 10);
    REQUIRE_FALSE(sut.can_consume(13));
    sut.restore(5);
    REQUIRE(sut.temporary_willpower() == 10);
    REQUIRE_FALSE(sut.can_consume(13));
    sut.set_permanent_willpower(18);
    sut.restore(5);
    REQUIRE(sut.temporary_willpower() == 15);
    REQUIRE(sut.can_consume(13));
  }

  SECTION("should read and write correctly to JSON")
  {
    power::willpower stub(10, 8);

    power::willpower sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut.permanent_willpower() == stub.permanent_willpower() );
    REQUIRE(sut.temporary_willpower() == stub.temporary_willpower() );
  }
}
