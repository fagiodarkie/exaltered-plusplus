#pragma once

#include <list>
#include <map>
#include <string>
#include <algorithm>
#include "common/reverse_search.h"
#include "text/character_text_constants.h"
#include "serialisation/json_constants.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace ability
{
  using namespace model::text::ability;

  enum class ability_enum
  {
    MELEE_LIGHT = 0, MELEE_MEDIUM, MELEE_HEAVY, ARCHERY, THROWN, MARTIAL_ARTS, RESISTANCE, STEALTH, DODGE, ATHLETICS,
    WAR, TECHNOLOGY, MANEUVER, MEDITATION, MEDICINE, LOGIC, ACADEMICS, CRAFT, ECONOMY, AWARENESS,
    PERFORMANCE, PRESENCE, DECEIT, POLITICS, DIPLOMACY, INTIMIDATION, INTEGRITY, RELATIONS, INTENTIONS, EMPATHY
  };

  static const std::list<ability_enum> ABILITIES = {
    ability_enum::MELEE_LIGHT, ability_enum::MELEE_MEDIUM, ability_enum::MELEE_HEAVY, ability_enum::ARCHERY, ability_enum::THROWN, ability_enum::MARTIAL_ARTS, ability_enum::RESISTANCE, ability_enum::STEALTH, ability_enum::DODGE, ability_enum::ATHLETICS,
    ability_enum::WAR, ability_enum::TECHNOLOGY, ability_enum::MANEUVER, ability_enum::MEDITATION, ability_enum::MEDICINE, ability_enum::LOGIC, ability_enum::ACADEMICS, ability_enum::CRAFT, ability_enum::ECONOMY, ability_enum::AWARENESS,
    ability_enum::PERFORMANCE, ability_enum::PRESENCE, ability_enum::DECEIT, ability_enum::POLITICS, ability_enum::DIPLOMACY, ability_enum::INTIMIDATION, ability_enum::INTEGRITY, ability_enum::RELATIONS, ability_enum::INTENTIONS, ability_enum::EMPATHY
  };

  enum ability_category
  {
    COMBAT, SOCIAL, NARRATIVE
  };

  static const std::list<ability_category> ABILITY_CATEGORIES = { COMBAT, SOCIAL, NARRATIVE };

  static const std::map<ability_category, std::string> ABILITY_CATEGORY_NAMES = {
    { COMBAT,     ABILITY_CATEGORY_PHYSICAL    },
    { SOCIAL,     ABILITY_CATEGORY_SOCIAL    },
    { NARRATIVE,  ABILITY_CATEGORY_MENTAL }
  };

  static const std::list<ability_enum> ABILITY_WITH_SUB_ABILITIES = {
     ability_enum::MANEUVER, ability_enum::TECHNOLOGY, ability_enum::CRAFT
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
      { ability_enum::TECHNOLOGY, { FIRE_TECH, WATER_TECH, WOOD_TECH, EARTH_TECH, AIR_TECH, NECRO_TECH, SURVIVAL_TECH }},
      { ability_enum::MANEUVER, { BEAST_MANEUVER, SHIP_MANEUVER, CHART_MANEUVER, FIRSTAGE_MANEUVER }},
      { ability_enum::CRAFT, { SMITH_CRAFT, FLETCHER_CRAFT, ENCHANT_CRAFT, ARMOR_CRAFT, LUTE_CRAFT }}
    };
  }

  static const std::map<ability_enum, std::string> ABILITY_NAME {
    { ability_enum::MELEE_LIGHT,      ABILITY_MELEE_LIGHT     },
    { ability_enum::MELEE_MEDIUM,     ABILITY_MELEE_MEDIUM    },
    { ability_enum::MELEE_HEAVY,      ABILITY_MELEE_HEAVY     },
    { ability_enum::ARCHERY,          ABILITY_ARCHERY         },
    { ability_enum::THROWN,           ABILITY_THROWN          },
    { ability_enum::MARTIAL_ARTS,     ABILITY_MARTIAL_ARTS    },
    { ability_enum::WAR,              ABILITY_WAR             },
    { ability_enum::TECHNOLOGY,       ABILITY_TECHNOLOGY      },
    { ability_enum::PERFORMANCE,      ABILITY_PERFORMANCE     },
    { ability_enum::PRESENCE,         ABILITY_PRESENCE        },
    { ability_enum::RESISTANCE,       ABILITY_RESISTANCE      },
    { ability_enum::INTEGRITY,        ABILITY_INTEGRITY       },
    { ability_enum::MEDITATION,       ABILITY_MEDITATION      },
    { ability_enum::ACADEMICS,        ABILITY_ACADEMICS       },
    { ability_enum::MEDICINE,         ABILITY_MEDICINE        },
    { ability_enum::LOGIC,    ABILITY_LOGIC    },
    { ability_enum::CRAFT,            ABILITY_CRAFT           },
    { ability_enum::STEALTH,          ABILITY_STEALTH         },
    { ability_enum::AWARENESS,        ABILITY_AWARENESS       },
    { ability_enum::DODGE,            ABILITY_DODGE           },
    { ability_enum::ATHLETICS,        ABILITY_ATHLETICS       },
    { ability_enum::MANEUVER,         ABILITY_MANEUVER        },
    { ability_enum::INTIMIDATION,     ABILITY_INTIMIDATION    },
    { ability_enum::INTENTIONS,       ABILITY_INTENTIONS      },
    { ability_enum::EMPATHY,          ABILITY_EMPATHY         },
    { ability_enum::ECONOMY,          ABILITY_ECONOMY         },
    { ability_enum::RELATIONS,        ABILITY_RELATIONS       },
    { ability_enum::DIPLOMACY,        ABILITY_DIPLOMACY       },
    { ability_enum::POLITICS,         ABILITY_POLITICS        },
    { ability_enum::DECEIT,           ABILITY_DECEIT          }
  };

  static const std::map<ability_category, std::list<ability_enum>> ABILITIES_IN_CATEGORY {
    { COMBAT,     { ability_enum::MELEE_LIGHT, ability_enum::MELEE_MEDIUM, ability_enum::MELEE_HEAVY, ability_enum::ARCHERY, ability_enum::THROWN, ability_enum::MARTIAL_ARTS, ability_enum::RESISTANCE, ability_enum::STEALTH, ability_enum::DODGE, ability_enum::ATHLETICS } },
    { NARRATIVE,  { ability_enum::WAR, ability_enum::TECHNOLOGY, ability_enum::MANEUVER, ability_enum::MEDITATION, ability_enum::MEDICINE, ability_enum::LOGIC, ability_enum::ACADEMICS, ability_enum::CRAFT, ability_enum::ECONOMY, ability_enum::AWARENESS } },
    { SOCIAL,     { ability_enum::PERFORMANCE, ability_enum::PRESENCE, ability_enum::DECEIT, ability_enum::POLITICS, ability_enum::DIPLOMACY, ability_enum::INTIMIDATION, ability_enum::INTEGRITY, ability_enum::RELATIONS, ability_enum::INTENTIONS, ability_enum::EMPATHY } }
  };

  static ability_category CATEGORY_OF_ABILITY(ability_enum ability)
  {
    return *std::find_if(ABILITY_CATEGORIES.begin(), ABILITY_CATEGORIES.end(), [ability](ability_category category) { return commons::contains(ABILITIES_IN_CATEGORY.at(category), ability); } );
  }

  class ability_name : public Serialisable {
  public:
    ability_enum ability_type;
    std::string subability;

    ability_name(ability_enum ab = ability_enum::CRAFT, std::string dec = ability_declination::NO_DECLINATION)
      : ability_type(ab), subability(dec) {}

    ability_name(const ability_name& other)
      : ability_type (other.ability_type), subability(other.subability) {}

    operator std::string() const
    {
      return name();
    }

    bool operator==(const ability_name& other) const
    {
      return (other.ability_type == ability_type) && (other.subability == subability);
    }

    bool operator< (const ability_name& other) const
    {
      return ability_type < other.ability_type
          || (ability_type == other.ability_type && subability < other.subability);
    }

    std::string name() const
    {
      auto ab_name = ABILITY_NAME.at(ability_type);
      if (!has_declination(ability_type))
        return ab_name;

      return ab_name + " (" + subability + ")";
    }

    void serialisation() override
    {
      synch(serialisation::json_constants::SLOT_ABILITY, ability_type);
      synch(serialisation::json_constants::SLOT_DECLINATION, subability);
    }

    virtual ~ability_name() { }
  };

}



