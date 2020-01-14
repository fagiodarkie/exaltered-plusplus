#pragma once

#include <list>
#include <map>
#include <string>
#include <algorithm>
#include "common/reverse_search.h"
#include "text/character_text_constants.h"

namespace ability
{
  using namespace model::text::ability;

  enum ability_enum
  {
    MELEE = 0, ARCHERY, THROWN, MARTIAL_ARTS, WAR,
    TECHNOLOGY, PERFORMANCE, PRESENCE, RESISTANCE, INTEGRITY,
    MEDITATION, MEDICINE, INVESTIGATION, ACADEMICS, CRAFT,
    STEALTH, AWARENESS, DODGE, ATHLETICS, PRESTIDIGITATION,
    MANEUVER, SOCIALISE, BUREAUCRACY, TEACHING
  };

  static const std::list<ability_enum> ABILITIES = {
    MELEE, ARCHERY, THROWN, MARTIAL_ARTS, WAR,
    TECHNOLOGY, PERFORMANCE, PRESENCE, RESISTANCE, INTEGRITY,
    MEDITATION, MEDICINE, INVESTIGATION, ACADEMICS, CRAFT,
    STEALTH, AWARENESS, DODGE, ATHLETICS, PRESTIDIGITATION,
    MANEUVER, SOCIALISE, BUREAUCRACY, TEACHING
  };

  enum ability_category
  {
    COMBAT, SOCIAL, NARRATIVE
  };

  static const std::list<ability_category> ABILITY_CATEGORIES = { COMBAT, SOCIAL, NARRATIVE };

  static const std::map<ability_category, std::string> ABILITY_CATEGORY_NAMES = {
    { COMBAT,     ABILITY_CATEGORY_SOCIAL    },
    { SOCIAL,     ABILITY_CATEGORY_COMBAT    },
    { NARRATIVE,  ABILITY_CATEGORY_NARRATIVE }
  };

  static const std::list<ability_enum> ABILITY_WITH_SUB_ABILITIES = {
    MANEUVER, TECHNOLOGY, CRAFT
  };

  static bool has_declination(ability_enum ability) {
    return std::find(ABILITY_WITH_SUB_ABILITIES.begin(), ABILITY_WITH_SUB_ABILITIES.end(), ability)
        != ABILITY_WITH_SUB_ABILITIES.end();
  }

  namespace ability_declination {
    static const std::string
    NO_DECLINATION = "NONE",

    FIRE_TECH    = "Fire",
    WATER_TECH   = "Water",
    WOOD_TECH    = "Wood",
    EARTH_TECH   = "Earth",
    AIR_TECH     = "Air",
    NECRO_TECH   = "Necrotech",
    SURVIVAL_TECH= "Survival",

    BEAST_MANEUVER    = "Beasts",
    SHIP_MANEUVER     = "Ships",
    CHART_MANEUVER    = "Charts",
    FIRSTAGE_MANEUVER = "First Age",

    SMITH_CRAFT     = "Smith",
    FLETCHER_CRAFT  = "Fletcher",
    ENCHANT_CRAFT   = "Enchanter",
    ARMOR_CRAFT     = "Armorer",
    LUTE_CRAFT      = "Lutist";

    static std::map<ability_enum, std::vector<std::string>> DECLINATIONS_OF_ABILITY = {
      { TECHNOLOGY, { FIRE_TECH, WATER_TECH, WOOD_TECH, EARTH_TECH, AIR_TECH, NECRO_TECH, SURVIVAL_TECH }},
      { MANEUVER, { BEAST_MANEUVER, SHIP_MANEUVER, CHART_MANEUVER, FIRSTAGE_MANEUVER }},
      { CRAFT, { SMITH_CRAFT, FLETCHER_CRAFT, ENCHANT_CRAFT, ARMOR_CRAFT, LUTE_CRAFT }}
    };
  }

  static const std::map<ability_enum, std::string> ABILITY_NAME {
    { MELEE,            ABILITY_MELEE            },
    { ARCHERY,          ABILITY_ARCHERY          },
    { THROWN,           ABILITY_THROWN           },
    { MARTIAL_ARTS,     ABILITY_MARTIAL_ARTS     },
    { WAR,              ABILITY_WAR              },
    { TECHNOLOGY,       ABILITY_TECHNOLOGY       },
    { PERFORMANCE,      ABILITY_PERFORMANCE      },
    { PRESENCE,         ABILITY_PRESENCE         },
    { RESISTANCE,       ABILITY_RESISTANCE       },
    { INTEGRITY,        ABILITY_INTEGRITY        },
    { MEDITATION,       ABILITY_MEDITATION       },
    { ACADEMICS,        ABILITY_ACADEMICS        },
    { MEDICINE,         ABILITY_MEDICINE         },
    { INVESTIGATION,    ABILITY_INVESTIGATION    },
    { TEACHING,         ABILITY_TEACHING         },
    { CRAFT,            ABILITY_CRAFT            },
    { STEALTH,          ABILITY_STEALTH          },
    { AWARENESS,        ABILITY_AWARENESS        },
    { DODGE,            ABILITY_DODGE            },
    { ATHLETICS,        ABILITY_ATHLETICS        },
    { PRESTIDIGITATION, ABILITY_PRESTIDIGITATION },
    { MANEUVER,         ABILITY_MANEUVER         },
    { SOCIALISE,        ABILITY_SOCIALISE        },
    { BUREAUCRACY,      ABILITY_BUREAUCRACY      }
  };

  static const std::map<ability_category, std::list<ability_enum>> ABILITIES_IN_CATEGORY {
    { COMBAT,     { MELEE,      ARCHERY,      THROWN,   MARTIAL_ARTS, WAR,            RESISTANCE,   AWARENESS,        DODGE     } },
    { NARRATIVE,  { TECHNOLOGY, MEDITATION,   MEDICINE, CRAFT,        STEALTH,        ATHLETICS,    PRESTIDIGITATION, MANEUVER  } },
    { SOCIAL,     { ACADEMICS,  PERFORMANCE,  PRESENCE, INTEGRITY,    INVESTIGATION,  SOCIALISE,    BUREAUCRACY,      TEACHING  } }
  };

  static ability_category CATEGORY_OF_ABILITY(ability_enum ability)
  {
    return *std::find_if(ABILITY_CATEGORIES.begin(), ABILITY_CATEGORIES.end(), [ability](ability_category category) { return commons::contains(ABILITIES_IN_CATEGORY.at(category), ability); } );
  }

  struct detailed_ability {
    ability_enum ability;
    std::string declination;

    detailed_ability(ability_enum ab, std::string dec = ability_declination::NO_DECLINATION)
      : ability(ab), declination(dec) {}

    detailed_ability(const detailed_ability& other)
      : ability (other.ability), declination(other.declination) {}

    bool operator==(const detailed_ability& other) const
    {
      return (other.ability == ability) && (other.declination == declination);
    }

    bool operator< (const detailed_ability& other) const
    {
      return ability < other.ability
          || (ability == other.ability && declination < other.declination);
    }

    std::string name() const
    {
      auto ab_name = ABILITY_NAME.at(ability);
      if (has_declination(ability))
        return ab_name;

      return ab_name + " (" + declination + ")";
    }
  };

}
