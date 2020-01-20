#include "../thirdparty/catch/catch.hpp"

#include "narrative/specialisation_purchase.h"
#include "character.h"

TEST_CASE("Specialisation Purchase")
{
  SECTION("should create new Specialisation purchase")
  {
    narrative::specialisation_purchase sut(3, ability::ability_enum::MEDICINE, "On the field");

    REQUIRE(sut.ability() == ability::ability_enum::MEDICINE);
    REQUIRE(sut.amount() == 3);
  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    c->ability(ability::ability_enum::MEDICINE).add(ability::specialisation("Bandages", 1));
    narrative::specialisation_purchase sut(2, ability::ability_enum::MEDICINE, "On the field");
    narrative::specialisation_purchase sut2(3, ability::ability_enum::MEDICINE, "Bandages");
    REQUIRE(c->get(ability::ability_enum::MEDICINE).get(sut.specialisation_name()).value() == 0);
    REQUIRE(c->get(ability::ability_enum::MEDICINE).get(sut2.specialisation_name()).value() == 1);
    sut.apply(c);
    sut2.apply(c);
    REQUIRE(c->get(ability::ability_enum::MEDICINE).get( sut.specialisation_name()) == sut.amount());
    REQUIRE(c->get(ability::ability_enum::MEDICINE).get(sut2.specialisation_name()) == sut2.amount());
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::specialisation_purchase sut(3, ability::ability_enum::MEDICINE, "On the field");

    std::string data;
    REQUIRE_NOTHROW(data = sut.serialise());

    narrative::specialisation_purchase stub;
    stub.deserialise(data);
    REQUIRE(stub.description() == sut.description());
    REQUIRE(stub.key() == sut.key());
    REQUIRE(stub.ability() == sut.ability());
    REQUIRE(stub.amount() == sut.amount());
  }

}
