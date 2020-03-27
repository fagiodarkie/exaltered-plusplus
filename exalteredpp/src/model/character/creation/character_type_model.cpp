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
                         const std::string& character_type_name)
      : primary_category_attribute_value(primary_category_attribute_value),
        secondary_category_attribute_value(secondary_category_attribute_value),
        tertiary_category_attribute_value(tertiary_category_attribute_value),
        starting_ability_points(starting_ability_points),
        max_std_ability_points_on_creation(max_std_ability_points_on_creation),
        max_ability_points_on_creation(max_ability_points_on_creation),
        min_ability_points_on_favorite_abilities(min_ability_points_on_favorite_abilities),
        favored_abilities(favored_abilities),
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
        type(type),
        character_type_name(character_type_name)
    {
      if (character_type_name.empty())
        this->character_type_name = CHARACTER_TYPE_NAMES.at(type);
    }

    character_type_model::character_type_model(const character_type_model &other)
      : primary_category_attribute_value(other.primary_category_attribute_value),
        secondary_category_attribute_value(other.secondary_category_attribute_value),
        tertiary_category_attribute_value(other.tertiary_category_attribute_value),
        starting_ability_points(other.starting_ability_points),
        max_std_ability_points_on_creation(other.max_std_ability_points_on_creation),
        max_ability_points_on_creation(other.max_ability_points_on_creation),
        min_ability_points_on_favorite_abilities(other.min_ability_points_on_favorite_abilities),
        favored_abilities(other.favored_abilities),
        caste_abilities(other.caste_abilities),
        starting_specialisations(other.starting_specialisations),
        starting_permanent_essence(other.starting_permanent_essence),
        starting_darkana(other.starting_darkana),
        starting_virtue_points(other.starting_virtue_points),
        max_std_virtue_points(other.max_std_virtue_points),
        max_virtue_points(other.max_virtue_points),
        starting_background_points(other.starting_background_points),
        starting_bonus_points(other.starting_bonus_points),
        starting_charms(other.starting_charms),
        is_supernatural(other.is_supernatural),
        type(other.type),
        character_type_name(other.character_type_name) { }

    character_type_model character_type_model::operator=(const character_type_model& o)
    {
      primary_category_attribute_value          = o.primary_category_attribute_value;
      secondary_category_attribute_value        = o.secondary_category_attribute_value;
      tertiary_category_attribute_value         = o.tertiary_category_attribute_value;
      starting_ability_points                   = o.starting_ability_points;
      max_std_ability_points_on_creation        = o.max_std_ability_points_on_creation;
      max_ability_points_on_creation            = o.max_ability_points_on_creation;
      min_ability_points_on_favorite_abilities  = o.min_ability_points_on_favorite_abilities;
      favored_abilities                         = o.favored_abilities;
      caste_abilities                           = o.caste_abilities;
      starting_specialisations                  = o.starting_specialisations;
      starting_permanent_essence                = o.starting_permanent_essence;
      starting_darkana                          = o.starting_darkana;
      starting_virtue_points                    = o.starting_virtue_points;
      max_std_virtue_points                     = o.max_std_virtue_points;
      max_virtue_points                         = o.max_virtue_points;
      starting_background_points                = o.starting_background_points;
      starting_bonus_points                     = o.starting_bonus_points;
      starting_charms                           = o.starting_charms;

      is_supernatural                           = o.is_supernatural;
      type                                      = o.type;
      character_type_name                       = o.character_type_name;
      return *this;
    }

    const character_type_model character_type_model::MORTAL_TEST(5, 4, 3,
                                                       10, 3, 0, 0, 0, 0,
                                                       0, 1, 1,
                                                       5, 3, 5,
                                                       7, 18, 0, false, character_type::TYPE_MORTAL_EXTRA);

    const character_type_model character_type_model::MORTAL_EXTRA(5, 4, 3,
                                                       22, 3, 5, 0, 0, 0,
                                                       0, 1, 1,
                                                       5, 3, 5,
                                                       7, 18, 0, false, character_type::TYPE_MORTAL_EXTRA);

    const character_type_model character_type_model::MORTAL_HERO(6, 5, 4,
                                                       22, 3, 5, 0, 1, 0,
                                                       0, 1, 1,
                                                       5, 4, 5,
                                                       7, 18, 0, false, character_type::TYPE_MORTAL_HERO);

    const character_type_model character_type_model::TERRESTRIAL_EXALT(8, 6, 4,
                                                       34, 3, 5, 12, 5, 5,
                                                       3, 2, 1,
                                                       5, 4, 5,
                                                       7, 10, 10, true, character_type::TYPE_TERRESTRIAL_EXALT);

    const character_type_model character_type_model::SOLAR_EXALT(8, 6, 4,
                                                       34, 3, 5, 12, 5, 5,
                                                       3, 2, 2,
                                                       5, 4, 5,
                                                       7, 10, 10, true, character_type::TYPE_SOLAR_EXALT);

    const character_type_model character_type_model::ABYSSAL_EXALT(8, 6, 4,
                                                       34, 3, 5, 12, 5, 5,
                                                       3, 2, 2,
                                                       5, 4, 5,
                                                       7, 10, 10, true, character_type::TYPE_ABYSSAL_EXALT);

    const character_type_model character_type_model::INFERNAL_EXALT(8, 6, 4,
                                                       34, 3, 5, 12, 5, 0,
                                                       3, 2, 2,
                                                       5, 4, 5,
                                                       7, 10, 10, true, character_type::TYPE_INFERNAL_EXALT);

    const character_type_model& character_type_model::get_by_character_type(character_type type)
    {
      switch(type)
        {
        case character_type::TYPE_MORTAL_EXTRA:
          return MORTAL_TEST;

        case character_type::TYPE_MORTAL_HERO:
          return MORTAL_HERO;

        case character_type::TYPE_TERRESTRIAL_EXALT:
          return TERRESTRIAL_EXALT;

        case character_type::TYPE_ABYSSAL_EXALT:
          return ABYSSAL_EXALT;

        case character_type::TYPE_SOLAR_EXALT:
          return SOLAR_EXALT;

        case character_type::TYPE_INFERNAL_EXALT:
          return INFERNAL_EXALT;

        default:
          throw exception::invalid_parameter();
        }
    }

  }
}
