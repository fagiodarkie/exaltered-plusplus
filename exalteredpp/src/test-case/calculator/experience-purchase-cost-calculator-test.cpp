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
    mortal->set_attribute(attribute::STRENGTH, 3);
    auto cost = calculator::purchase_cost_calculator::cost_of(narrative::ATTRIBUTE, std::make_shared<narrative::attribute_purchase>(attribute::STRENGTH, 4)).for_who(mortal);
    REQUIRE(cost == 12);
  }

  SECTION("should compute the right cost for ability purchases")
  {
    mortal->set_ability(ability::WAR, ability::ability_group(ability::WAR, {ability::ability(ability::ability_declination::NO_DECLINATION, 2)}));
    mortal->set_ability(ability::MELEE, ability::ability_group(ability::MELEE));
    mortal->set_ability(ability::TECHNOLOGY, ability::ability_group(ability::TECHNOLOGY, {ability::ability(ability::ability_declination::AIR_TECH, 3), ability::ability(ability::ability_declination::WOOD_TECH, 4)}));
    mortal->get_ability_group(ability::TECHNOLOGY).set_favourite(true, ability::ability_declination::AIR_TECH);
    auto warcost = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::WAR, 3)).for_who(mortal);
    auto techcost = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::detailed_ability(ability::TECHNOLOGY, ability::ability_declination::AIR_TECH), 4)).for_who(mortal);
    auto meleecost = calculator::purchase_cost_calculator::cost_of(narrative::ABILITY,
                     std::make_shared<narrative::ability_purchase>(ability::MELEE, 1)).for_who(mortal);
    // normal
    REQUIRE(warcost == 4);
    // favorite
    REQUIRE(techcost == 5);
    // first dot
    REQUIRE(meleecost == 3);
  }
}
