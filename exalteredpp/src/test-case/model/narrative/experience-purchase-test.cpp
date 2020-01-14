#include "../thirdparty/catch/catch.hpp"

#include "narrative/experience.h"
#include "narrative/attribute_purchase.h"
#include "narrative/ability_purchase.h"
#include "narrative/specialisation_purchase.h"
#include "narrative/essence_purchase.h"
#include "narrative/willpower_purchase.h"
#include "narrative/virtue_purchase.h"
#include "narrative/vice_purchase.h"
#include "character.h"

TEST_CASE("Experience Purchase")
{
  SECTION("should create new attribute purchase")
  {
    narrative::experience_purchase sut(narrative::ATTRIBUTE, 4, std::make_shared<narrative::attribute_purchase>());

    REQUIRE(sut.cost() == 4);
    REQUIRE(sut.purchase_type() == narrative::ATTRIBUTE);
  }

  SECTION("should serialise and deserialise correctly each purchase type")
  {
    narrative::experience_purchase sut_1(narrative::ATTRIBUTE,  4, std::make_shared<narrative::attribute_purchase>());
    narrative::experience_purchase sut_2(narrative::ABILITY,    4, std::make_shared<narrative::ability_purchase>());
    narrative::experience_purchase sut_3(narrative::SPECIALISATION, 4, std::make_shared<narrative::specialisation_purchase>());
    narrative::experience_purchase sut_4(narrative::ESSENCE,    4, std::make_shared<narrative::essence_purchase>());
    narrative::experience_purchase sut_5(narrative::WILLPOWER,  4, std::make_shared<narrative::willpower_purchase>());
    narrative::experience_purchase sut_6(narrative::VIRTUE,     4, std::make_shared<narrative::virtue_purchase>());
    narrative::experience_purchase sut_7(narrative::VICE,       4, std::make_shared<narrative::vice_purchase>());

    for (auto sut : {sut_1, sut_2, sut_3, sut_4, sut_5, sut_6, sut_7})
      {
        std::string data = sut.serialise();
        narrative::experience_purchase stub;

        stub.deserialise(data);
        REQUIRE(stub.cost() == sut.cost());
        REQUIRE(stub.purchase()->key() == sut.purchase()->key());
        REQUIRE(stub.purchase()->description() == sut.purchase()->description());
        REQUIRE(stub.purchase_type() == sut.purchase_type());
      }
  }
}
