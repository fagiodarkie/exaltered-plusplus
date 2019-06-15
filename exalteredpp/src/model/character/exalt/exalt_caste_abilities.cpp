#include "exalt/exalt_caste.h"

namespace character {
  namespace exalt {

    using character::creation::character_type;

    QList<ability> exalt_caste::_WARRIOR_CASTE = { ability::WAR,
                                                   ability::MELEE,
                                                   ability::ARCHERY,
                                                   ability::THROWN,
                                                   ability::MARTIAL_ARTS },

    exalt_caste::_PRIEST_CASTE = { ability::PRESENCE,
                                   ability::INTEGRITY,
                                   ability::PERFORMANCE,
                                   ability::RESISTANCE,
                                   ability::SURVIVAL },

    exalt_caste::_SCIENTIST_CASTE = { ability::INVESTIGATION,
                                      ability::ACADEMICS,
                                      ability::MEDITATION,
                                      ability::CRAFT,
                                      ability::MEDICINE },

    exalt_caste::_STEALTH_CASTE = { ability::LARCENY,
                                    ability::ATHLETICS,
                                    ability::DODGE,
                                    ability::AWARENESS,
                                    ability::STEALTH },

    exalt_caste::_DIPLOMAT_CASTE = { ability::SOCIALISE,
                                     ability::BUREAUCRACY,
                                     ability::MANEUVER,
                                     ability::ACADEMICS,
                                     ability::TEACHING };

    const QMap<caste, QList<ability>> exalt_caste::ABILITIES_OF_CASTE = {

      { caste::NO_CASTE,    QList<ability>() },

      { caste::DAWN,        _WARRIOR_CASTE },
      { caste::DUSK,        _WARRIOR_CASTE },
      { caste::SLAYER,      _WARRIOR_CASTE },

      { caste::ZENITH,      _PRIEST_CASTE },
      { caste::MIDNIGHT,    _PRIEST_CASTE },
      { caste::MALEFACTOR,  _PRIEST_CASTE },

      { caste::TWILIGHT,    _SCIENTIST_CASTE },
      { caste::DAYBREAK,    _SCIENTIST_CASTE },
      { caste::DEFILER,     _SCIENTIST_CASTE },

      { caste::NIGHT,       _STEALTH_CASTE },
      { caste::DAY,         _STEALTH_CASTE },
      { caste::SCOURGE,     _STEALTH_CASTE },

      { caste::ECLIPSE,     _DIPLOMAT_CASTE },
      { caste::MOONSHADOW,  _DIPLOMAT_CASTE },
      { caste::FIEND,       _DIPLOMAT_CASTE },

      { caste::WATER,       { ability::BUREAUCRACY,
                              ability::INVESTIGATION,
                              ability::LARCENY,
                              ability::MARTIAL_ARTS,
                              ability::MANEUVER } },

      { caste::EARTH,       { ability::AWARENESS,
                              ability::CRAFT,
                              ability::INTEGRITY,
                              ability::RESISTANCE,
                              ability::WAR } },

      { caste::AIR,         { ability::ACADEMICS,
                              ability::MEDITATION,
                              ability::STEALTH,
                              ability::THROWN,
                              ability::TEACHING } },

      { caste::WOOD,        { ability::ARCHERY,
                              ability::MEDICINE,
                              ability::PERFORMANCE,
                              ability::MANEUVER,
                              ability::SURVIVAL } },

      { caste::FIRE,        { ability::ATHLETICS,
                              ability::DODGE,
                              ability::MELEE,
                              ability::PRESENCE,
                              ability::SOCIALISE } }
    };

    const QMap<character_type, QList<caste>> exalt_caste::CASTES_OF_EXALT_TYPE = {
      { character_type::TYPE_MORTAL_HERO,       { caste::NO_CASTE } },
      { character_type::TYPE_MORTAL_EXTRA,      { caste::NO_CASTE } },
      { character_type::TYPE_TERRESTRIAL_EXALT, { caste::AIR,     caste::WATER, caste::FIRE, caste::WOOD, caste::EARTH               } },
      { character_type::TYPE_SOLAR_EXALT,       { caste::DAWN,    caste::ZENITH, caste::TWILIGHT, caste::NIGHT, caste::ECLIPSE      } },
      { character_type::TYPE_ABYSSAL_EXALT,     { caste::DUSK,    caste::MIDNIGHT, caste::DAYBREAK, caste::DAY, caste::MOONSHADOW   } },
      { character_type::TYPE_INFERNAL_EXALT,    { caste::SLAYER,  caste::MALEFACTOR, caste::DEFILER, caste::SCOURGE, caste::FIEND } },
    };

    const QMap<caste, QString> exalt_caste::NAME_OF_CASTE = {
      { caste::NO_CASTE    , "None"       },

      { caste::DAWN        , "Dawn"       },
      { caste::ZENITH      , "Zenith"     },
      { caste::TWILIGHT    , "Twilight"   },
      { caste::NIGHT       , "Night"      },
      { caste::ECLIPSE     , "Eclipse"    },
      { caste::DUSK        , "Dusk"       },
      { caste::MIDNIGHT    , "Midnight"   },
      { caste::DAYBREAK    , "Daybreak"   },
      { caste::DAY         , "Day"        },
      { caste::MOONSHADOW  , "Moonshadow" },
      { caste::SLAYER      , "Slayer"     },
      { caste::MALEFACTOR  , "Malefactor" },
      { caste::DEFILER     , "Defiler"    },
      { caste::SCOURGE     , "Scourge"    },
      { caste::FIEND       , "Fiend"      },
      { caste::FIRE        , "Fire"       },
      { caste::WATER       , "Water"      },
      { caste::EARTH       , "Earth"      },
      { caste::AIR         , "Air"        },
      { caste::WOOD        , "Wood"       }
    };

  }
}
