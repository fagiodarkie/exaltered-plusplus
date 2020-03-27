#include "exalt/exalt_caste.h"


namespace character {
  namespace exalt {

    using character::creation::character_type;

    std::vector<ability_enum> exalt_caste::_WARRIOR_CASTE = { ability_enum::WAR,
                                                              ability_enum::MELEE_HEAVY,
                                                              ability_enum::MELEE_MEDIUM,
                                                              ability_enum::ARCHERY,
                                                              ability_enum::THROWN,
                                                              ability_enum::MARTIAL_ARTS },

    exalt_caste::_PRIEST_CASTE = { ability_enum::PRESENCE,
                                   ability_enum::INTEGRITY,
                                   ability_enum::PERFORMANCE,
                                   ability_enum::RESISTANCE,
                                   ability_enum::EMPATHY,
                                   ability_enum::INTIMIDATION },

    exalt_caste::_SCIENTIST_CASTE = { ability_enum::LOGIC,
                                      ability_enum::ACADEMICS,
                                      ability_enum::MEDITATION,
                                      ability_enum::CRAFT,
                                      ability_enum::MEDICINE,
                                      ability_enum::TECHNOLOGY },

    exalt_caste::_STEALTH_CASTE = { ability_enum::DECEIT,
                                    ability_enum::ATHLETICS,
                                    ability_enum::DODGE,
                                    ability_enum::AWARENESS,
                                    ability_enum::STEALTH,
                                    ability_enum::MELEE_LIGHT },

    exalt_caste::_DIPLOMAT_CASTE = { ability_enum::DIPLOMACY,
                                     ability_enum::POLITICS,
                                     ability_enum::MANEUVER,
                                     ability_enum::ECONOMY,
                                     ability_enum::RELATIONS,
                                     ability_enum::INTENTIONS };

    const std::map<caste, std::vector<ability_enum>> exalt_caste::ABILITIES_OF_CASTE = {

      { caste::NO_CASTE,    std::vector<ability_enum>() },

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

      { caste::WATER,       { ability_enum::POLITICS,
                              ability_enum::LOGIC,
                              ability_enum::DECEIT,
                              ability_enum::MARTIAL_ARTS,
                              ability_enum::MANEUVER,
                              ability_enum::MELEE_LIGHT } },

      { caste::EARTH,       { ability_enum::AWARENESS,
                              ability_enum::CRAFT,
                              ability_enum::INTEGRITY,
                              ability_enum::RESISTANCE,
                              ability_enum::WAR,
                              ability_enum::MELEE_HEAVY } },

      { caste::AIR,         { ability_enum::ACADEMICS,
                              ability_enum::MEDITATION,
                              ability_enum::STEALTH,
                              ability_enum::THROWN,
                              ability_enum::EMPATHY,
                              ability_enum::INTENTIONS } },

      { caste::WOOD,        { ability_enum::ARCHERY,
                              ability_enum::MEDICINE,
                              ability_enum::PERFORMANCE,
                              ability_enum::DIPLOMACY,
                              ability_enum::TECHNOLOGY,
                              ability_enum::ECONOMY } },

      { caste::FIRE,        { ability_enum::ATHLETICS,
                              ability_enum::DODGE,
                              ability_enum::MELEE_MEDIUM,
                              ability_enum::PRESENCE,
                              ability_enum::INTIMIDATION,
                              ability_enum::RELATIONS } }
    };

    const std::map<character_type, std::vector<caste>> exalt_caste::CASTES_OF_EXALT_TYPE = {
      { character_type::TYPE_MORTAL_HERO,       { caste::NO_CASTE } },
      { character_type::TYPE_MORTAL_EXTRA,      { caste::NO_CASTE } },
      { character_type::TYPE_TERRESTRIAL_EXALT, { caste::AIR,     caste::WATER, caste::FIRE, caste::WOOD, caste::EARTH               } },
      { character_type::TYPE_SOLAR_EXALT,       { caste::DAWN,    caste::ZENITH, caste::TWILIGHT, caste::NIGHT, caste::ECLIPSE      } },
      { character_type::TYPE_ABYSSAL_EXALT,     { caste::DUSK,    caste::MIDNIGHT, caste::DAYBREAK, caste::DAY, caste::MOONSHADOW   } },
      { character_type::TYPE_INFERNAL_EXALT,    { caste::SLAYER,  caste::MALEFACTOR, caste::DEFILER, caste::SCOURGE, caste::FIEND } },
    };

    const std::map<caste, std::string> exalt_caste::NAME_OF_CASTE = {
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
