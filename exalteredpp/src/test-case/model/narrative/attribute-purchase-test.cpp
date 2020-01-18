#include "../thirdparty/catch/catch.hpp"

#include "narrative/attribute_purchase.h"
#include "character.h"

TEST_CASE("Attribute Purchase")
{
  SECTION("should create new attribute purchase")
  {
    narrative::attribute_purchase sut(attribute::attribute_enum::STRENGTH, 3);

    REQUIRE(sut.attribute() == attribute::attribute_enum::STRENGTH);
    REQUIRE(sut.amount() == 3);

  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    c->set(attribute::attribute_enum::STRENGTH, 0);
    narrative::attribute_purchase sut(attribute::attribute_enum::STRENGTH, 3);
    sut.apply(c);
    REQUIRE(c->attribute(attribute::attribute_enum::STRENGTH) == 3);
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::attribute_purchase sut(attribute::attribute_enum::STRENGTH, 5);

    std::string data;
    REQUIRE_NOTHROW(data = sut.serialise());

    narrative::attribute_purchase stub;
    stub.deserialise(data);
    REQUIRE(stub.description() == sut.description());
    REQUIRE(stub.key() == sut.key());
    REQUIRE(stub.attribute() == sut.attribute());
    REQUIRE(stub.amount() == sut.amount());
  }
}
