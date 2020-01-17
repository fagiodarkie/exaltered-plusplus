#ifndef ATTACK_DEFINES_H
#define ATTACK_DEFINES_H

namespace calculator {

  enum target_vd {
    PHYSICAL_PARRY,
    PHYSICAL_DODGE,
    MENTAL_PARRY,
    MENTAL_DODGE
  };

  enum attack_attribute {
    NON_PARRYABLE,
    NON_DODGEABLE,
    UNEXPECTED,
    COUNTERATTACK,
    POLARISED,
    WITH_MINIMUM,
    NO_ATTRIBUTE
  };

  enum body_target {
    VITAL_PART,
    TRUNK,
    LEFT_UPPER,
    RIGHT_UPPER,
    LEFT_LOWER,
    RIGHT_LOWER,
    NO_TARGET
  };

  enum damage_type {
    BASHING,
    LETHAL,
    AGGRAVATED
  };

}

#endif // ATTACK_DEFINES_H
