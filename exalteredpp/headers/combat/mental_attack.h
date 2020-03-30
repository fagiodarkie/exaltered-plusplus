#ifndef MENTAL_ATTACK_H
#define MENTAL_ATTACK_H

#include "character.h"
#include "derived_value_calculator.h"
#include "dice_roller/abstract_dice_roller.h"
#include "attack_defines.h"
#include <vector>

namespace mental_combat {

  using combat::attack_attribute;
  using combat::target_vd;

  class attack_declaration;
  class pre_precision_defense_declaration;
  class post_precision_defense_declaration;
  class precision_roll;
  class vd_application;
  class raw_impulse_computation;
  class post_soak_damage;
  class final_damage;
  class outcome;

#define STANDARD_CONSTRUCTORS(classname) public: \
    classname(classname&& o) : combat_step(o._atk) { } \
    classname(const classname& o) : combat_step(o._atk) { } \
    void operator=(const classname& o) { _atk = o._atk; } \
  private:\
    classname(std::shared_ptr<social_attack_descriptor> atk) : combat_step(atk) { }

  class combat_step {
  protected:
    struct social_attack_descriptor
    {
      unsigned int action_penalty = 0;
      std::vector<attack_attribute> attack_attributes;
      std::shared_ptr<character::character> attacker, defender;
      target_vd vd = target_vd::MENTAL_DODGE;

      attribute::attribute_enum attack_attribute;
      ability::ability_name attack_ability;

      int
      // info for attacker
      vd_value = 0,
      precision_external_bonus = 0,
      precision_internal_bonus = 0,
      soak = 0,

      // info for defender
      precision_roll_result = 0,
      bonus_damage = 0,

      // info for everybody
      precision_dice = 0,
      raw_impulses_dice = 0,
      post_soak_impulses = 0,
      final_damage_result = 0,
      final_damage_multiplier = 0;

      bool
      is_long_term_attack = false,
      has_fixed_result = false,
      precision_rolled = false,
      damage_rolled = false;

    };

  };


}
#endif // MENTAL_ATTACK_H
