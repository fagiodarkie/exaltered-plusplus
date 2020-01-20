#ifndef ATTACK_DEFINES_H
#define ATTACK_DEFINES_H

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

}

#endif // ATTACK_DEFINES_H
