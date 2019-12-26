#pragma once

#include <list>
#include <map>
#include <string>
#include <algorithm>
#include "common/reverse_search.h"

namespace character
{
  namespace ability_names {
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
      { COMBAT, "Combat"}, { SOCIAL, "Social"}, { NARRATIVE, "Narrative" }
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

    struct detailed_ability {
      ability_enum ability;
      std::string declination;

      detailed_ability(ability_enum ab, std::string dec = ability_declination::NO_DECLINATION)
        : ability(ab), declination(dec) {}

      detailed_ability(const detailed_ability& other)
        : ability (other.ability), declination(other.declination) {}

      bool operator==(const detailed_ability& other)
      {
        return (other.ability == ability) && (other.declination == declination);
      }
    };

    static const std::map<ability_enum, std::string> ABILITY_NAME {
      { MELEE,            "Melee"           },
      { ARCHERY,          "Archery"         },
      { THROWN,           "Thrown"          },
      { MARTIAL_ARTS,     "Martial Arts"    },
      { WAR,              "War"             },
      { TECHNOLOGY,       "Technology"      },
      { PERFORMANCE,      "Performance"     },
      { PRESENCE,         "Presence"        },
      { RESISTANCE,       "Resistance"      },
      { INTEGRITY,        "Integrity"       },
      { MEDITATION,       "Meditation"      },
      { ACADEMICS,        "Academics"       },
      { MEDICINE,         "Medicine"        },
      { INVESTIGATION,    "Investigation"   },
      { TEACHING,         "Teaching"        },
      { CRAFT,            "Craft"           },
      { STEALTH,          "Stealth"         },
      { AWARENESS,        "Awareness"       },
      { DODGE,            "Dodge"           },
      { ATHLETICS,        "Athletics"       },
      { PRESTIDIGITATION, "Prestidigitation"},
      { MANEUVER,         "Maneuver"        },
      { SOCIALISE,        "Socialise"       },
      { BUREAUCRACY,      "Bureaucracy"     }
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

  }
}
