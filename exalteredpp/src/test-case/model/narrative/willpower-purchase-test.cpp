#include "../thirdparty/catch/catch.hpp"

#include "narrative/willpower_purchase.h"
#include "character.h"

TEST_CASE("Willpower Purchase")
{
  SECTION("should create new willpower purchase")
  {
    narrative::willpower_purchase sut(3);

    REQUIRE(sut.amount() == 3);
  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    REQUIRE(c->willpower().permanent_willpower() == 0);
    narrative::willpower_purchase sut(3);
    sut.apply(c);
    REQUIRE(c->willpower().permanent_willpower() == 3);
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::willpower_purchase sut(5);

    std::string data;
    REQUIRE_NOTHROW(data = sut.serialise());

    narrative::willpower_purchase stub;
    stub.deserialise(data);
    REQUIRE(stub.description() == sut.description());
    REQUIRE(stub.key() == sut.key());
    REQUIRE(stub.amount() == sut.amount());
  }
}
