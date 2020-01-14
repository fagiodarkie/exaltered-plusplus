#include "../thirdparty/catch/catch.hpp"

#include "narrative/ability_purchase.h"
#include "character.h"

TEST_CASE("Ability Purchase")
{
  SECTION("should create new ability purchase")
  {
    narrative::ability_purchase sut(ability::MEDICINE, 3);

    REQUIRE(sut.ability() == ability::MEDICINE);
    REQUIRE(sut.amount() == 3);

    narrative::ability_purchase sut2(ability::detailed_ability(ability::TECHNOLOGY, "Herbs"), 5);

    REQUIRE(sut2.ability().declination == "Herbs");
    REQUIRE(sut2.amount() == 5);
  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    REQUIRE(c->get_ability(ability::MEDICINE) == 0);
    REQUIRE(c->get_ability(ability::TECHNOLOGY) == 0);
    narrative::ability_purchase sut(ability::MEDICINE, 3);
    narrative::ability_purchase sut2(ability::detailed_ability(ability::TECHNOLOGY, "Herbs"), 5);
    sut.apply(c);
    sut2.apply(c);
    REQUIRE(c->get_ability(ability::MEDICINE) == 3);
    REQUIRE(c->get_ability(ability::TECHNOLOGY, sut2.ability().declination) == 5);
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::ability_purchase sut(ability::detailed_ability(ability::TECHNOLOGY, "Herbs"), 5);

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
