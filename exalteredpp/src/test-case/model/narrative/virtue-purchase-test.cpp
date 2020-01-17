#include "../thirdparty/catch/catch.hpp"

#include "narrative/virtue_purchase.h"
#include "character.h"

TEST_CASE("Virtue Purchase")
{
  SECTION("should create new Virtue purchase")
  {
    narrative::virtue_purchase sut(3, virtues::COMPASSION);

    REQUIRE(sut.virtue() == virtues::COMPASSION);
    REQUIRE(sut.amount() == 3);
  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    REQUIRE(c->virtue(virtues::COMPASSION).value() == 1);
    narrative::virtue_purchase sut(3, virtues::COMPASSION);
    sut.apply(c);
    REQUIRE(c->virtue(virtues::COMPASSION).value() == 3);
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::virtue_purchase sut(5, virtues::COMPASSION);

    std::string data;
    REQUIRE_NOTHROW(data = sut.serialise());

    narrative::virtue_purchase stub;
    stub.deserialise(data);
    REQUIRE(stub.description() == sut.description());
    REQUIRE(stub.key() == sut.key());
    REQUIRE(stub.virtue() == sut.virtue());
    REQUIRE(stub.amount() == sut.amount());
  }
}
