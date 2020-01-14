#include "../thirdparty/catch/catch.hpp"

#include "narrative/specialisation_purchase.h"
#include "character.h"

TEST_CASE("Specialisation Purchase")
{
  SECTION("should create new Specialisation purchase")
  {
    narrative::specialisation_purchase sut(3, ability::MEDICINE, "On the field");

    REQUIRE(sut.ability() == ability::MEDICINE);
    REQUIRE(sut.amount() == 3);
  }

  SECTION("should apply successfully to character")
  {
    std::shared_ptr<character::character> c = std::make_shared<character::character>("");
    c->set_ability(ability::MEDICINE, ability::ability_group(ability::MEDICINE,
      {ability::ability(ability::ability_declination::NO_DECLINATION)},
      {ability::specialisation("Bandages")}));
    narrative::specialisation_purchase sut(2, ability::MEDICINE, "On the field");
    narrative::specialisation_purchase sut2(3, ability::MEDICINE, "Bandages");
    REQUIRE_THROWS(c->get_ability_group(ability::MEDICINE).get_specialisation(sut.specialisation_name()));
    REQUIRE(c->get_ability_group(ability::MEDICINE).get_specialisation(sut2.specialisation_name()).get_specialisation_value() == 1);
    sut.apply(c);
    sut2.apply(c);
    REQUIRE(c->get_ability_group(ability::MEDICINE).get_specialisation(sut.specialisation_name()).get_specialisation_value() == sut.amount());
    REQUIRE(c->get_ability_group(ability::MEDICINE).get_specialisation(sut2.specialisation_name()).get_specialisation_value() == sut2.amount());
  }

  SECTION("should serialise and deserialise successfully")
  {
    narrative::specialisation_purchase sut(3, ability::MEDICINE, "On the field");

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
