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

    namespace ability_declination {
      static const std::string
      NO_DECLINATION = "NONE",

      FIRE_CRAFT    = "Fire",
      WATER_CRAFT   = "Water",
      WOOD_CRAFT    = "Wood",
      EARTH_CRAFT   = "Earth",
      AIR_CRAFT     = "Air",
      NECRO_CRAFT   = "Necrotech",

      BEAST_MANEUVER    = "Beasts",
      SHIP_MANEUVER     = "Ships",
      CHART_MANEUVER    = "Charts",
      FIRSTAGE_MANEUVER = "First Age";
    }

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
