#include "exalt/exalt_caste.h"

namespace character {
  namespace exalt {

    using character::creation::character_type;

    const QMap<exalt_caste::caste, QList<ability>> exalt_caste::ABILITIES_OF_CASTE = {
      { exalt_caste::DAWN,        _WARRIOR_CASTE },
      { exalt_caste::DUSK,        _WARRIOR_CASTE },
      { exalt_caste::SLAYER,      _WARRIOR_CASTE },

      { exalt_caste::ZENITH,      _PRIEST_CASTE },
      { exalt_caste::MIDNIGHT,    _PRIEST_CASTE },
      { exalt_caste::MALEFACTOR,  _PRIEST_CASTE },

      { exalt_caste::TWILIGHT,    _SCIENTIST_CASTE },
      { exalt_caste::DAYBREAK,    _SCIENTIST_CASTE },
      { exalt_caste::DEFILER,     _SCIENTIST_CASTE },

      { exalt_caste::NIGHT,       _STEALTH_CASTE },
      { exalt_caste::DAY,         _STEALTH_CASTE },
      { exalt_caste::SCOURGE,     _STEALTH_CASTE },

      { exalt_caste::ECLIPSE,     _DIPLOMAT_CASTE },
      { exalt_caste::MOONSHADOW,  _DIPLOMAT_CASTE },
      { exalt_caste::FIEND,       _DIPLOMAT_CASTE },

      { exalt_caste::WATER,       { ability::BUREAUCRACY,
                                    ability::INVESTIGATION,
                                    ability::LARCENY,
                                    ability::MARTIAL_ARTS,
                                    ability::MANEUVER } },

      { exalt_caste::EARTH,       { ability::AWARENESS,
                                    ability::CRAFT,
                                    ability::INTEGRITY,
                                    ability::RESISTANCE,
                                    ability::WAR } },

      { exalt_caste::AIR,         { ability::ACADEMICS,
                                    ability::MEDITATION,
                                    ability::STEALTH,
                                    ability::THROWN,
                                    ability::TEACHING } },

      { exalt_caste::WOOD,        { ability::ARCHERY,
                                    ability::MEDICINE,
                                    ability::PERFORMANCE,
                                    ability::MANEUVER,
                                    ability::SURVIVAL } },

      { exalt_caste::FIRE,        { ability::ATHLETICS,
                                    ability::DODGE,
                                    ability::MELEE,
                                    ability::PRESENCE,
                                    ability::SOCIALISE } }
    };

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

    const QMap<character_type, QList<exalt_caste::caste>> exalt_caste::CASTES_OF_EXALT_TYPE = {
      { character_type::TYPE_TERRESTRIAL_EXALT, { AIR, WATER, FIRE, WOOD, EARTH               } },
      { character_type::TYPE_SOLAR_EXALT,       { DAWN, ZENITH, TWILIGHT, NIGHT, ECLIPSE      } },
      { character_type::TYPE_ABYSSAL_EXALT,     { DUSK, MIDNIGHT, DAYBREAK, DAY, MOONSHADOW   } },
      { character_type::TYPE_INFERNAL_EXALT,    { SLAYER, MALEFACTOR, DEFILER, SCOURGE, FIEND } },
    };

    const QMap<exalt_caste::caste, QString> exalt_caste::NAME_OF_CASTE = {
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
