#include "../thirdparty/catch/catch.hpp"

#include "experience_purchase_cost_calculator.h"

#include "narrative/experience.h"
#include "narrative/attribute_purchase.h"
#include "narrative/ability_purchase.h"
#include "narrative/specialisation_purchase.h"
#include "narrative/essence_purchase.h"
#include "narrative/willpower_purchase.h"
#include "narrative/virtue_purchase.h"
#include "narrative/vice_purchase.h"
#include "character.h"

TEST_CASE("Experience Purchase Cost Calculator")
{
  std::shared_ptr<character::character> mortal = std::make_shared<character::character>(""),
      exalt = std::make_shared<character::character>("");

  SECTION("should compute the right cost for attribute purchases")
  {
    mortal->set(attribute::attribute_enum::STRENGTH, 3);
    auto cost = calculator::purchase_cost_calculator::cost_of(narrative::ATTRIBUTE, std::make_shared<narrative::attribute_purchase>(attribute::attribute_enum::STRENGTH, 4)).for_who(mortal);
    auto cost2 = calculator::purchase_cost_calculator::cost_of(narrative::ATTRIBUTE, std::make_shared<narrative::attribute_purchase>(attribute::attribute_enum::STRENGTH, 5)).for_who(mortal);
    REQUIRE(cost == 12);
    REQUIRE(cost2 == 28);
  }

  SECTION("should compute the right cost for ability purchases")
  {
    mortal->set(ability::ability_enum::WAR, 2);
    mortal->ability(ability::ability_enum::TECHNOLOGY, ability::ability_declination::WOOD_TECH) = 3;
    mortal->ability(ability::ability_enum::TECHNOLOGY, ability::ability_declination::WOOD_TECH).set_favored();
    auto warcost = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::ability_enum::WAR, 3)).for_who(mortal);
    auto techcost = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::ability_name(ability::ability_enum::TECHNOLOGY, ability::ability_declination::WOOD_TECH), 4)).for_who(mortal);
    auto meleecost = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::ability_enum::MELEE_LIGHT, 1)).for_who(mortal);

    auto warcost2 = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::ability_enum::WAR, 4)).for_who(mortal);
    auto techcost2 = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::ability_name(ability::ability_enum::TECHNOLOGY, ability::ability_declination::WOOD_TECH), 5)).for_who(mortal);
    auto meleecost2 = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::ability_enum::MELEE_LIGHT, 2)).for_who(mortal);
    // normal
    REQUIRE(warcost == 4);
    // favorite
    REQUIRE(techcost == 5);
    // first dot
    REQUIRE(meleecost == 3);

    // normal
    REQUIRE(warcost2 == 10);
    // favorite
    REQUIRE(techcost2 == 12);
    // first dot
    REQUIRE(meleecost2 == 5);
  }


  SECTION("should compute the right cost for specialisation purchases")
  {
    mortal->set(ability::ability_enum::WAR, 2);
    mortal->ability(ability::ability_enum::TECHNOLOGY, ability::ability_declination::WOOD_TECH) = 3;
    auto generic_ability_cost = calculator::purchase_cost_calculator::cost_of(narrative::SPECIALISATION,
                     std::make_shared<narrative::specialisation_purchase>(1, ability::ability_enum::WAR, "strategy")).for_who(mortal);
    auto generic_ability_cost_2 = calculator::purchase_cost_calculator::cost_of(narrative::SPECIALISATION,
                     std::make_shared<narrative::specialisation_purchase>(2, ability::ability_enum::WAR, "strategy")).for_who(mortal);
    auto specific_ability_cost = calculator::purchase_cost_calculator::cost_of(narrative::SPECIALISATION,
                     std::make_shared<narrative::specialisation_purchase>(1, ability::ability_name(ability::ability_enum::TECHNOLOGY, ability::ability_declination::WOOD_TECH), "axework"))
        .for_who(mortal);
    auto specific_ability_cost_2 = calculator::purchase_cost_calculator::cost_of(narrative::SPECIALISATION,
                     std::make_shared<narrative::specialisation_purchase>(2, ability::ability_name(ability::ability_enum::TECHNOLOGY, ability::ability_declination::WOOD_TECH), "axework"))
        .for_who(mortal);

    REQUIRE( generic_ability_cost == 3);
    REQUIRE(specific_ability_cost == 3);
    REQUIRE( generic_ability_cost_2 == 6);
    REQUIRE(specific_ability_cost_2 == 6);
  }

  SECTION("should compute the right cost for essence purchases")
  {
    mortal->essence().set_permanent_essence(1);
    auto ep2cost = calculator::purchase_cost_calculator::cost_of(narrative::ESSENCE,
                     std::make_shared<narrative::essence_purchase>(2)).for_who(mortal);
    auto ep3cost = calculator::purchase_cost_calculator::cost_of(narrative::ESSENCE,
                     std::make_shared<narrative::essence_purchase>(3)).for_who(mortal);
    REQUIRE(ep2cost == 8);
    REQUIRE(ep3cost == 24);
  }


  SECTION("should compute the right cost for willpower purchases")
  {
    mortal->willpower().set_permanent_willpower(1);
    auto ep2cost = calculator::purchase_cost_calculator::cost_of(narrative::WILLPOWER,
                     std::make_shared<narrative::willpower_purchase>(2)).for_who(mortal);
    auto ep3cost = calculator::purchase_cost_calculator::cost_of(narrative::WILLPOWER,
                     std::make_shared<narrative::willpower_purchase>(3)).for_who(mortal);
    REQUIRE(ep2cost == 2);
    REQUIRE(ep3cost == 6);
  }


  SECTION("should compute the right cost for virtue purchases")
  {
    mortal->virtue(virtues::COMPASSION).set_value(1);
    auto virtuecost = calculator::purchase_cost_calculator::cost_of(narrative::VIRTUE,
                     std::make_shared<narrative::virtue_purchase>(2, virtues::COMPASSION)).for_who(mortal);
    auto virtuecost2 = calculator::purchase_cost_calculator::cost_of(narrative::VIRTUE,
                     std::make_shared<narrative::virtue_purchase>(3, virtues::COMPASSION)).for_who(mortal);
    REQUIRE(virtuecost == 3);
    REQUIRE(virtuecost2 == 9);
  }


  SECTION("should compute the right cost for vice purchases")
  {
    mortal->set_vice(mortal->vice(), 1);
    auto vicecost = calculator::purchase_cost_calculator::cost_of(narrative::VICE,
                     std::make_shared<narrative::vice_purchase>(2)).for_who(mortal);
    auto vicecost2 = calculator::purchase_cost_calculator::cost_of(narrative::VICE,
                     std::make_shared<narrative::vice_purchase>(3)).for_who(mortal);
    REQUIRE(vicecost == 3);
    REQUIRE(vicecost2 == 9);
  }
}
