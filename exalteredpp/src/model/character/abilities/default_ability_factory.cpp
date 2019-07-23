#include "abilities/default_ability_factory.h"


namespace character {
  ability_group default_ability_factory::get_ability_group(ability_names::ability_enum abilityname) const
  {
    std::vector<ability> abilities;
    switch(abilityname)
      {
      case ability_names::MANEUVER:
        abilities.push_back(ability(ability_names::ability_declination::SHIP_MANEUVER));
        abilities.push_back(ability(ability_names::ability_declination::CHART_MANEUVER));
        abilities.push_back(ability(ability_names::ability_declination::SHIP_MANEUVER));
        abilities.push_back(ability(ability_names::ability_declination::FIRSTAGE_MANEUVER));
      break;
      case ability_names::CRAFT:
          abilities.push_back(ability(ability_names::ability_declination::AIR_CRAFT));
          abilities.push_back(ability(ability_names::ability_declination::FIRE_CRAFT));
          abilities.push_back(ability(ability_names::ability_declination::EARTH_CRAFT));
          abilities.push_back(ability(ability_names::ability_declination::WOOD_CRAFT));
          abilities.push_back(ability(ability_names::ability_declination::WATER_CRAFT));
          abilities.push_back(ability(ability_names::ability_declination::NECRO_CRAFT));
      break;
      default:
        abilities.push_back(ability(ability_names::ability_declination::NO_DECLINATION));
      break;
      }

    auto category = std::find_if(ability_names::ABILITY_CATEGORIES.begin(),
                                 ability_names::ABILITY_CATEGORIES.end(),
                                  [abilityname](ability_names::ability_category category_set) -> bool {
                                    return commons::contains(ability_names::ABILITIES_IN_CATEGORY.at(category_set), abilityname);
                                  });

    ability_group result(ability_names::ABILITY_NAME.at(abilityname), *category, abilities);
    return result;
  }
}
