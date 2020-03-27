#pragma once

#include "attributes/attribute_names.h"
#include <list>
#include <map>

namespace character {
  namespace creation {

    enum character_type {
      TYPE_MORTAL_EXTRA,
      TYPE_MORTAL_HERO,
      TYPE_TERRESTRIAL_EXALT,
      TYPE_SOLAR_EXALT,
      TYPE_ABYSSAL_EXALT,
      TYPE_INFERNAL_EXALT
    };

    static const std::map<character_type, std::string> CHARACTER_TYPE_NAMES =
      { { TYPE_MORTAL_EXTRA,         "Mortal Extra"    },
        { TYPE_MORTAL_HERO,          "Mortal Hero"     },
        { TYPE_TERRESTRIAL_EXALT,    "Terrestrial Exalt"  },
        { TYPE_SOLAR_EXALT,          "Solar Exalt"        },
        { TYPE_ABYSSAL_EXALT,        "Abyssal Exalt"      },
        { TYPE_INFERNAL_EXALT,       "Infernal Exalt"     }
      };

    static const std::list<character_type> CHARACTER_TYPE_LIST = {
      TYPE_MORTAL_EXTRA,
      TYPE_MORTAL_HERO,
      TYPE_TERRESTRIAL_EXALT,
      TYPE_SOLAR_EXALT,
      TYPE_ABYSSAL_EXALT,
      TYPE_INFERNAL_EXALT
    };

    class character_type_model
    {
    public:
      character_type_model(unsigned int primary_category_attribute_value,
                           unsigned int secondary_category_attribute_value,
                           unsigned int tertiary_category_attribute_value,

                           unsigned int starting_ability_points,
                           unsigned int max_std_ability_points_on_creation,
                           unsigned int max_ability_points_on_creation,
                           unsigned int min_ability_points_on_favorite_abilities,
                           unsigned int favored_abilities,
                           unsigned int caste_abilities,

                           unsigned int starting_specialisations,
                           unsigned int starting_permanent_essence,
                           unsigned int starting_darkana,

                           unsigned int starting_virtue_points,
                           unsigned int max_std_virtue_points,
                           unsigned int max_virtue_points,

                           unsigned int starting_background_points,
                           unsigned int starting_bonus_points,
                           unsigned int starting_charms,

                           bool is_supernatural,
                           character_type type,
                           const std::string& character_type_name = "");

      character_type_model(const character_type_model& other);

      character_type_model operator=(const character_type_model& o);

      static const character_type_model MORTAL_TEST, MORTAL_EXTRA, MORTAL_HERO,
        TERRESTRIAL_EXALT, SOLAR_EXALT, ABYSSAL_EXALT, INFERNAL_EXALT;

      unsigned int primary_category_attribute_value,
        secondary_category_attribute_value,
        tertiary_category_attribute_value,
        starting_ability_points,
        max_std_ability_points_on_creation,
        max_ability_points_on_creation,
        min_ability_points_on_favorite_abilities,
        favored_abilities,
        caste_abilities,
        starting_specialisations,
        starting_permanent_essence,
        starting_darkana,
        starting_virtue_points,
        max_std_virtue_points,
        max_virtue_points,
        starting_background_points,
        starting_bonus_points,
        starting_charms
      ;
      bool is_supernatural;
      character_type type;
      std::string character_type_name;

      static const character_type_model& get_by_character_type(character_type type);

    };
  }
}
