#include "../thirdparty/catch/catch.hpp"

#include "narrative/vice_purchase.h"
#include "character.h"

TEST_CASE("Vice Purchase")
{
  SECTION("should create new Vice purchase")
  {
    narrative::vice_purchase sut(3);

    REQUIRE(sut.amount() == 3);
  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    REQUIRE(c->vice_value() == 1);
    narrative::vice_purchase sut(3);
    sut.apply(c);
    REQUIRE(c->vice_value() == 3);
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::vice_purchase sut(5);

    std::string data;
    REQUIRE_NOTHROW(data = sut.serialise());

    narrative::vice_purchase stub;
    stub.deserialise(data);
    REQUIRE(stub.description() == sut.description());
    REQUIRE(stub.key() == sut.key());
    REQUIRE(stub.amount() == sut.amount());
  }
}
