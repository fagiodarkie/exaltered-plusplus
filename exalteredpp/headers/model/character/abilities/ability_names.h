#pragma once

#include <QMap>
#include <QString>

namespace character
{
  namespace ability_names {
    enum ability_name
    {
      MELEE, ARCHERY, THROWN, MARTIAL_ARTS, WAR,
      SURVIVAL, PERFORMANCE, PRESENCE, RESISTANCE, INTEGRITY,
      OCCULT, MEDICINE, INVESTIGATION, KNOWLEDGE, CRAFT,
      STEALTH, AWARENESS, DODGE, ATHLETICS, LARCENY,
      MANEUVER, SOCIALISE, BUREAUCRACY, LANGUAGE
    };

    enum ability_category
    {
      COMBAT, SOCIAL, NARRATIVE
    };

    namespace ability_declination {
      static const QString
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

    static const QMap<ability_name, QString> ABILITY_NAME {
      { MELEE,            "Melee"         },
      { ARCHERY,          "Archery"       },
      { THROWN,           "Thrown"        },
      { MARTIAL_ARTS,     "Martial Arts"  },
      { WAR,              "War"           },
      { SURVIVAL,         "Survival"      },
      { PERFORMANCE,      "Performance"   },
      { PRESENCE,         "Presence"      },
      { RESISTANCE,       "Resistance"    },
      { INTEGRITY,        "Integrity"     },
      { OCCULT,           "Occult"        },
      { MEDICINE,         "Medicine"      },
      { INVESTIGATION,    "Investigation" },
      { KNOWLEDGE,        "Knowledge"     },
      { CRAFT,            "Craft"         },
      { STEALTH,          "Stealth"       },
      { AWARENESS,        "Awareness"     },
      { DODGE,            "Dodge"         },
      { ATHLETICS,        "Athletics"     },
      { LARCENY,          "Larceny"       },
      { MANEUVER,         "Maneuver"      },
      { SOCIALISE,        "Socialise"     },
      { BUREAUCRACY,      "Bureaucracy"   },
      { LANGUAGE,         "Language"      }
    };

    static const QMap<ability_category, QList<ability_name>> ABILITY_CATEGORY {
      { COMBAT, { MELEE, ARCHERY, THROWN, MARTIAL_ARTS, WAR, RESISTANCE, AWARENESS, DODGE } },
      { NARRATIVE, { SURVIVAL, OCCULT, MEDICINE, CRAFT, STEALTH, ATHLETICS, LARCENY, MANEUVER } },
      { SOCIAL, { KNOWLEDGE, PERFORMANCE, PRESENCE, INTEGRITY, INVESTIGATION, SOCIALISE, BUREAUCRACY, LANGUAGE } }
    };

  }
}
