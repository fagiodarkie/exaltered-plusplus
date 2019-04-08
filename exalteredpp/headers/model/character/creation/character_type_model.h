#pragma once

#include "attributes/attribute_names.h"
#include <QList>

namespace character {
  namespace creation {

    enum character_type {
      MORTAL_EXTRA,
      MORTAL_HERO,
      TERRESTRIAL_EXALT,
      SOLAR_EXALT,
      ABYSSAL_EXALT,
      INFERNAL_EXALT
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

                           unsigned int starting_specialisations,
                           unsigned int starting_permanent_essence,
                           unsigned int starting_darkana,

                           unsigned int starting_virtue_points,
                           unsigned int max_std_virtue_points,
                           unsigned int max_virtue_points,

                           unsigned int starting_background_points,
                           unsigned int starting_bonus_points,
                           unsigned int starting_charms,

                           bool has_caste_abilities);

      static const character_type_model MORTAL_EXTRA, MORTAL_HERO, TERRESTRIAL_EXALT, SOLAR_EXALT;

      const unsigned int primary_category_attribute_value,
        secondary_category_attribute_value,
        tertiary_category_attribute_value,
        starting_ability_points,
        max_std_ability_points_on_creation,
        max_ability_points_on_creation,
        min_ability_points_on_favorite_abilities,
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

      static const character_type_model get_by_character_type(character_type character_type);

      const bool has_caste_abilities;
    };
  }
}
