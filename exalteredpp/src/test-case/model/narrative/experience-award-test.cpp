#include "../thirdparty/catch/catch.hpp"

#include "narrative/experience_award.h"

TEST_CASE("Experience award")
{
  SECTION("should create correctly")
  {
    narrative::experience_award sut(narrative::NARRATION, 3);

    REQUIRE(sut.type() == narrative::NARRATION);
    REQUIRE(sut.amount() == 3);
  }

  SECTION("should serialise and deserialise correctly")
  {
    narrative::experience_award sut(narrative::NARRATION, 4);

    sut.set_description("description");

    std::string data = sut.serialise();

    narrative::experience_award stub;
    stub.deserialise(data);

    REQUIRE(sut.type() == stub.type());
    REQUIRE(sut.amount() == stub.amount());
    REQUIRE(sut.description() == stub.description());
    REQUIRE(sut.summary() == stub.summary());
  }
}
