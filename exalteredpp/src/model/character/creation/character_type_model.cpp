#include "creation/character_type_model.h"

#include "invalid_parameter.h"

namespace character {
  namespace creation {

    character_type_model::character_type_model(unsigned int primary_category_attribute_value,
                         unsigned int secondary_category_attribute_value,
                         unsigned int tertiary_category_attribute_value,
                         unsigned int starting_ability_points,
                         unsigned int max_std_ability_points_on_creation,
                         unsigned int max_ability_points_on_creation,
                         unsigned int min_ability_points_on_favorite_abilities,
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
                         bool has_caste_abilities,
                         bool is_supernatural,
                         enum character_type character_type,
                         const QString& character_type_name)
      : primary_category_attribute_value(primary_category_attribute_value),
        secondary_category_attribute_value(secondary_category_attribute_value),
        tertiary_category_attribute_value(tertiary_category_attribute_value),
        starting_ability_points(starting_ability_points),
        max_std_ability_points_on_creation(max_std_ability_points_on_creation),
        max_ability_points_on_creation(max_ability_points_on_creation),
        min_ability_points_on_favorite_abilities(min_ability_points_on_favorite_abilities),
        caste_abilities(caste_abilities),
        starting_specialisations(starting_specialisations),
        starting_permanent_essence(starting_permanent_essence),
        starting_darkana(starting_darkana),
        starting_virtue_points(starting_virtue_points),
        max_std_virtue_points(max_std_virtue_points),
        max_virtue_points(max_virtue_points),
        starting_background_points(starting_background_points),
        starting_bonus_points(starting_bonus_points),
        starting_charms(starting_charms),
        is_supernatural(is_supernatural),
        character_type(character_type),
        character_type_name(character_type_name)
    {
      if (character_type_name == nullptr)
        this->character_type_name = CHARACTER_TYPE_NAMES.value(character_type);
    }

    const character_type_model character_type_model::MORTAL_EXTRA = character_type_model(5, 4, 3,
                                                             18, 3, 0, 0, 0,
                                                             0, 1, 1,
                                                             7, 3, 5,
                                                             7, 18, 0, false, character_type::MORTAL_EXTRA);

    const character_type_model character_type_model::MORTAL_HERO = character_type_model(6, 5, 4,
                                                             18, 3, 5, 10, 0,
                                                             0, 1, 1,
                                                             7, 4, 5,
                                                             7, 18, 0, false, character_type::MORTAL_HERO);

    const character_type_model character_type_model::TERRESTRIAL_EXALT = character_type_model(8, 6, 4,
                                                             28, 3, 5, 10, 5,
                                                             3, 2, 1,
                                                             7, 4, 5,
                                                             7, 10, 10, true, character_type::TERRESTRIAL_EXALT);

    const character_type_model character_type_model::SOLAR_EXALT = character_type_model(8, 6, 4,
                                                             28, 3, 5, 10, 5,
                                                             3, 2, 2,
                                                             7, 4, 5,
                                                             7, 10, 10, true, character_type::SOLAR_EXALT);

    const character_type_model character_type_model::ABYSSAL_EXALT = character_type_model(8, 6, 4,
                                                             28, 3, 5, 10, 5,
                                                             3, 2, 2,
                                                             7, 4, 5,
                                                             7, 10, 10, true, character_type::SOLAR_EXALT);

    const character_type_model character_type_model::INFERNAL_EXALT = character_type_model(8, 6, 4,
                                                             28, 3, 5, 10, 0,
                                                             3, 2, 2,
                                                             7, 4, 5,
                                                             7, 10, 10, true, character_type::SOLAR_EXALT);

    const character_type_model character_type_model::get_by_character_type(enum character_type character_type)
    {
      switch(character_type)
        {
        case character_type::MORTAL_EXTRA:
          return MORTAL_EXTRA;

        case character_type::MORTAL_HERO:
          return MORTAL_HERO;

        case character_type::TERRESTRIAL_EXALT:
          return TERRESTRIAL_EXALT;

        case character_type::ABYSSAL_EXALT:
        case character_type::SOLAR_EXALT:
        case character_type::INFERNAL_EXALT:
          return SOLAR_EXALT;
        default:
          throw exception::invalid_parameter();
        }
    }


  }
}
