#include "abilities/default_ability_factory.h"

#include <QList>

namespace character {
  ability_group default_ability_factory::get_ability_group(ability_names::ability_name abilityname) const
  {
    QList<ability> abilities;
    switch(abilityname)
      {
      case ability_names::MANEUVER:
        abilities.append({
          ability(ability_names::ability_declination::SHIP_MANEUVER),
          ability(ability_names::ability_declination::CHART_MANEUVER),
          ability(ability_names::ability_declination::SHIP_MANEUVER),
          ability(ability_names::ability_declination::FIRSTAGE_MANEUVER)
      });
      break;
      case ability_names::CRAFT:
        abilities.append({
          ability(ability_names::ability_declination::AIR_CRAFT),
          ability(ability_names::ability_declination::FIRE_CRAFT),
          ability(ability_names::ability_declination::EARTH_CRAFT),
          ability(ability_names::ability_declination::WOOD_CRAFT),
          ability(ability_names::ability_declination::WATER_CRAFT),
          ability(ability_names::ability_declination::NECRO_CRAFT),
      });
      break;
        default:
        abilities.append(ability(ability_names::ability_declination::NO_DECLINATION));
        break;
      }

    QList<ability_names::ability_category> categories = ability_names::ABILITY_CATEGORY.keys();

    auto category = std::find_if(categories.begin(),
                                 categories.end(),
                                  [abilityname](ability_names::ability_category category_set) -> bool {
                                    return ability_names::ABILITY_CATEGORY[category_set].contains(abilityname);
                                  });

    ability_group result(ability_names::ABILITY_NAME.value(abilityname), *category, abilities);
    return result;
  }
}
