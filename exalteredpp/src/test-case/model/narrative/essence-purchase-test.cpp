#include "../thirdparty/catch/catch.hpp"

#include "narrative/essence_purchase.h"
#include "character.h"

TEST_CASE("Essence Purchase")
{
  SECTION("should create new Essence purchase")
  {
    narrative::essence_purchase sut(3);

    REQUIRE(sut.amount() == 3);
  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    REQUIRE(c->essence().permanent_essence() == 1);
    narrative::essence_purchase sut(3);
    sut.apply(c);
    REQUIRE(c->essence().permanent_essence() == 3);
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::essence_purchase sut(5);

    std::string data;
    REQUIRE_NOTHROW(data = sut.serialise());

    narrative::essence_purchase stub;
    stub.deserialise(data);
    REQUIRE(stub.description() == sut.description());
    REQUIRE(stub.key() == sut.key());
    REQUIRE(stub.amount() == sut.amount());
  }
}
