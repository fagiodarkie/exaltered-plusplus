#ifndef ATTACK_DEFINES_H
#define ATTACK_DEFINES_H

#include "dice_roller/dice_roller.h"

namespace combat {

  enum class target_vd {
    PHYSICAL_PARRY,
    PHYSICAL_DODGE,
    MENTAL_PARRY,
    MENTAL_DODGE
  };

  enum class attack_attribute {
    NON_PARRYABLE,
    NON_DODGEABLE,
    UNEXPECTED,
    COUNTERATTACK,
    POLARISED,
    WITH_MINIMUM,
    NO_ATTRIBUTE,
    CONCEDED,
    PERFECT
  };

  enum class defense_attribute {
    PARRIES_UNEXPECTED,
    CONCEDED,
    PERFECT
  };

  enum class body_target {
    VITAL_PART,
    TRUNK,
    LEFT_UPPER,
    RIGHT_UPPER,
    LEFT_LOWER,
    RIGHT_LOWER,
    NO_TARGET
  };

  enum class damage_type_enum {
    BASHING,
    LETHAL,
    AGGRAVATED,
    SPIRITUAL
  };


  class body_part_roller
  {
  public:
    body_part_roller() {}

    body_target roll_body_part() const
    {
      std::mt19937 _random = std::mt19937(std::random_device()());
      std::uniform_int_distribution<unsigned int> _distribution = std::uniform_int_distribution<unsigned int>(1, 10);

      auto die = _distribution(_random);

      switch(die)
        {
        case 1:
          return body_target::VITAL_PART;
        case 2: case 3: case 4:
          return body_target::TRUNK;
        case 5:
          return body_target::LEFT_UPPER;
        case 6:
          return body_target::RIGHT_UPPER;
        case 7: case 8:
          return body_target::LEFT_LOWER;
        case 9: case 0:
          return body_target::RIGHT_LOWER;
        }
      return body_target::NO_TARGET;
    }
  };


}

#endif // ATTACK_DEFINES_H
