#include "abilities/default_ability_factory.h"

#include <QList>

namespace character {
  ability_group default_ability_factory::get_ability_group(ability_name abilityname) const
  {
    QList<ability> abilities;
    switch(abilityname)
      {
      case MANEUVER:
        abilities.append({
          ability(ability_declination::SHIP_MANEUVER),
          ability(ability_declination::CHART_MANEUVER),
          ability(ability_declination::SHIP_MANEUVER),
          ability(ability_declination::FIRSTAGE_MANEUVER)
      });
      break;
      case CRAFT:
        abilities.append({
          ability(ability_declination::AIR_CRAFT),
          ability(ability_declination::FIRE_CRAFT),
          ability(ability_declination::EARTH_CRAFT),
          ability(ability_declination::WOOD_CRAFT),
          ability(ability_declination::WATER_CRAFT),
          ability(ability_declination::NECRO_CRAFT),
      });
      break;
        default:
        abilities.append(ability(ability_declination::NO_DECLINATION));
        break;
      }

    ability_group result(ABILITY_NAME.value(abilityname), abilities);
    return result;
  }
}
