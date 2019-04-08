#include "creation/character_type_model.h"

namespace character {
  namespace creation {

    const character_type_model character_type_model::MORTAL_EXTRA = character_type_model(5, 4, 3,
                                                             18, 3, 0, 0,
                                                             0, 1, 1,
                                                             7, 3, 5,
                                                             7, 18, 0, false);

    const character_type_model character_type_model::MORTAL_HERO = character_type_model(6, 5, 4,
                                                             18, 3, 5, 10,
                                                             0, 1, 1,
                                                             7, 4, 5,
                                                             7, 18, 0, false);

    const character_type_model character_type_model::TERRESTRIAL_EXALT = character_type_model(8, 6, 4,
                                                             28, 3, 5, 10,
                                                             3, 2, 1,
                                                             7, 4, 5,
                                                             7, 10, 10, true);

    const character_type_model character_type_model::SOLAR_EXALT = character_type_model(8, 6, 4,
                                                             28, 3, 5, 10,
                                                             3, 2, 2,
                                                             7, 4, 5,
                                                             7, 10, 10, true);

    const character_type_model character_type_model::get_by_character_type(character_type character_type)
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
        }
    }


  }
}
