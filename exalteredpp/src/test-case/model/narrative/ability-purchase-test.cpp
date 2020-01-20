#include "../thirdparty/catch/catch.hpp"

#include "narrative/ability_purchase.h"
#include "character.h"

TEST_CASE("Ability Purchase")
{
  SECTION("should create new ability purchase")
  {
    narrative::ability_purchase sut(ability::ability_enum::MEDICINE, 3);

    REQUIRE(sut.ability() == ability::ability_enum::MEDICINE);
    REQUIRE(sut.amount() == 3);

    narrative::ability_purchase sut2(ability::ability_name(ability::ability_enum::TECHNOLOGY, "Herbs"), 5);

    REQUIRE(sut2.ability().subability == "Herbs");
    REQUIRE(sut2.amount() == 5);
  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    REQUIRE((int)c->get(ability::ability_enum::MEDICINE) == 0);
    REQUIRE((int)c->get(ability::ability_enum::TECHNOLOGY) == 0);
    narrative::ability_purchase sut(ability::ability_enum::MEDICINE, 3);
    narrative::ability_purchase sut2(ability::ability_name(ability::ability_enum::TECHNOLOGY, "Herbs"), 5);
    sut.apply(c);
    sut2.apply(c);
    REQUIRE((int)c->get(ability::ability_enum::MEDICINE) == 3);
    REQUIRE((int)c->get(ability::ability_enum::TECHNOLOGY, sut2.ability().subability) == 5);
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::ability_purchase sut(ability::ability_name(ability::ability_enum::TECHNOLOGY, "Herbs"), 5);

    std::string data;
    REQUIRE_NOTHROW(data = sut.serialise());

    narrative::ability_purchase stub;
    stub.deserialise(data);
    REQUIRE(stub.description() == sut.description());
    REQUIRE(stub.key() == sut.key());
    REQUIRE(stub.ability() == sut.ability());
    REQUIRE(stub.amount() == sut.amount());
  }
}
