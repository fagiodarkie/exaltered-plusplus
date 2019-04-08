#pragma once

#include <QMap>
#include <QString>

namespace character
{
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

  static const QMap<ability_name, ability_category> ABILITY_CATEGORY {
    { MELEE,        COMBAT  },
    { ARCHERY,      COMBAT  },
    { THROWN,       COMBAT  },
    { MARTIAL_ARTS, COMBAT  },
    { WAR,          COMBAT  },
    { RESISTANCE,   COMBAT  },
    { AWARENESS,    COMBAT  },
    { DODGE,        COMBAT  },

    { SURVIVAL,     NARRATIVE  },
    { OCCULT,       NARRATIVE  },
    { MEDICINE,     NARRATIVE  },
    { CRAFT,        NARRATIVE  },
    { STEALTH,      NARRATIVE  },
    { ATHLETICS,    NARRATIVE  },
    { LARCENY,      NARRATIVE  },
    { MANEUVER,     NARRATIVE  },

    { KNOWLEDGE,    SOCIAL  },
    { PERFORMANCE,  SOCIAL  },
    { PRESENCE,     SOCIAL  },
    { INTEGRITY,    SOCIAL  },
    { INVESTIGATION,SOCIAL  },
    { SOCIALISE,    SOCIAL  },
    { BUREAUCRACY,  SOCIAL  },
    { LANGUAGE,     SOCIAL  }
  };
}
