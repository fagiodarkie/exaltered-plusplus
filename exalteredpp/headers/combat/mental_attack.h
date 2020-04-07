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
  using combat::social_attack_outcome;

  class attack_declaration;
  class pre_precision_defense_declaration;
  class post_precision_defense_declaration;
  class precision_roll;
  class vd_application;
  class raw_impulse_computation;
  class final_impulses;
  class outcome;

#define STANDARD_CONSTRUCTORS(classname) public: \
    classname(classname&& o) : social_combat_step(o._atk) { } \
    classname(const classname& o) : social_combat_step(o._atk) { } \
    void operator=(const classname& o) { _atk = o._atk; } \
  private:\
    classname(std::shared_ptr<social_attack_descriptor> atk) : social_combat_step(atk) { }

  class social_combat_step {
  protected:
    struct social_attack_descriptor
    {
      unsigned int action_penalty = 0;
      std::vector<attack_attribute> attack_attributes;
      std::shared_ptr<character::character> attacker, defender;
      target_vd vd = target_vd::MENTAL_DODGE;

      attribute::attribute_enum attack_attribute;
      ability::ability_name attack_ability, attack_secondary_ability;
      character::social::specific targeted_specific;
      character::social::social_degrees target_degree;
      character::social::emotion targeted_emotion;
      social_attack_outcome outcome = social_attack_outcome::SUFFER;

      int
      // info for attacker
      vd_value = 0,
      precision_external_bonus = 0,
      precision_internal_bonus = 0,
      soak = 0,
      philosophy_value = 0,

      // info for defender
      precision_roll_result = 0,
      bonus_damage = 0, // INT + TWP

      // info for everybody
      precision_dice = 0,
      raw_impulses_dice = 0,
      post_soak_impulses = 0,
      final_damage_result = 0,
      final_damage_multiplier = 0;

      std::string philosophy_name;

      bool
      has_fixed_result = false,
      precision_rolled = false,
      damage_rolled = false,
      used_philosophy = false;

    };

    social_combat_step(std::shared_ptr<social_attack_descriptor> atk) : _atk(atk) { }
    std::shared_ptr<social_attack_descriptor> _atk;

  public:
    const std::shared_ptr<const social_attack_descriptor> attack_status() const
    {
      return _atk;
    }

    virtual ~social_combat_step() {}
  };

  class social_attack_declaration : public social_combat_step
  {
    friend class precision_roll;
    friend class post_precision_defense_declaration;

  public:
    static attack_declaration declare();
    static attack_declaration declare_as(std::initializer_list<attack_attribute> attributes);

    attack_declaration& is(std::vector<attack_attribute> attributes);
    attack_declaration& is(attack_attribute attribute);
    attack_declaration& is_not(attack_attribute attribute);
    attack_declaration& attacker(std::shared_ptr<character::character> attacker);

    pre_precision_defense_declaration defend() const;
    precision_roll roll_precision() const;

  private:

    social_attack_declaration() : social_combat_step (std::make_shared<social_attack_descriptor>()) { }
  };

}
#endif // MENTAL_ATTACK_H
