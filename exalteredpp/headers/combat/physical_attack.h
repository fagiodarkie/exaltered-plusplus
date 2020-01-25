#ifndef PHYSICAL_ATTACK_H
#define PHYSICAL_ATTACK_H

#include "attack_defines.h"
#include "weapon.h"
#include <vector>

#include "character.h"
#include "derived_value_calculator.h"
#include "dice_roller/abstract_dice_roller.h"

namespace combat {

  class attack_declaration;
  class pre_precision_defense_declaration;
  class post_precision_defense_declaration;
  class precision_roll;
  class vd_application;
  class raw_damage_and_position_computation;
  class post_soak_damage;
  class post_hardness_damage;
  class final_damage;
  class outcome;
  
  class combat_step {
  protected:
    struct attack_descriptor
    {
      unsigned int action_penalty = 0;
      equip::weapon weapon;
      std::vector<attack_attribute> attack_attributes;
      std::shared_ptr<character::character> attacker, defender;
      target_vd vd = target_vd::PHYSICAL_DODGE;

      int
      // info for attacker
      vd_value = 0,
      vd_balance = 0,
      damage_sacrificed = 0,
      precision_external_bonus = 0,
      precision_external_malus = 0,
      precision_internal_bonus = 0,
      precision_internal_malus = 0,
      soak = 0,
      armor_soak = 0,

      // info for defender
      precision_roll_result = 0,
      bonus_damage = 0,
      damage_attribute = 0,

      // info for everybody
      precision_dice = 0,
      raw_damage_dice = 0,
      post_soak_damage = 0,
      meters_pushed = 0,
      final_damage_result = 0,
      final_damage_reduction = 0,
      final_damage_multiplier = 0;

      bool
      has_fixed_result = false,
      precision_rolled = false,
      damage_rolled = false,
      tried_to_push = false,
      tried_to_knock = false,
      was_knocked_back = false,
      was_knocked_down = false,
      is_damage_from_minimum = false,
      body_part_rolled = false;

      body_target target = body_target::NO_TARGET;

      unsigned int raw_damage() const
      {
        bool attribute_forbidden = commons::contains(attack_attributes, attack_attribute::NO_ATTRIBUTE)
            || weapon.is(attack_attribute::NO_ATTRIBUTE);
        unsigned int attribute = attribute_forbidden
            ? 0
            : attacker ? attacker->attribute(weapon.damage_attribute())
                       : damage_attribute;

        return raw_damage_dice + attribute + weapon.base_damage();
      }

    };

    combat_step(std::shared_ptr<attack_descriptor> atk) : _atk(atk) { }
    std::shared_ptr<attack_descriptor> _atk;

  public:
    const std::shared_ptr<const attack_descriptor> attack_status() const
    {
      return _atk;
    }
  };

  class attack_declaration : public combat_step
  {
    friend class precision_roll;
    friend class post_precision_defense_declaration;

  public:
    static attack_declaration declare();
    static attack_declaration declare_as(std::initializer_list<attack_attribute> attributes);

    attack_declaration& is(std::initializer_list<attack_attribute> attributes);
    attack_declaration& is(attack_attribute attribute);
    attack_declaration& is_not(attack_attribute attribute);
    attack_declaration& with(const equip::weapon& w);
    attack_declaration& with_action_penalty(unsigned int vd_penalty);
    attack_declaration& attacker(std::shared_ptr<character::character> attacker);

    pre_precision_defense_declaration defend() const;
    precision_roll roll_precision() const;

  private:

    attack_declaration() : combat_step (std::make_shared<attack_descriptor>()) { }
  };

  class post_precision_defense_declaration : public combat_step
  {
    friend class attack_declaration;
    friend class precision_roll;

  public:
    std::vector<target_vd> possible_vds() const;

    vd_application dodge(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator) const;
    vd_application parry_with(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator, ability::ability_enum parry_ability) const;
    vd_application defend_with_value(target_vd vd, unsigned int vd_value);

  private:
    post_precision_defense_declaration(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class pre_precision_defense_declaration : public combat_step
  {
    friend class attack_declaration;
    friend class precision_roll;

  public:
    std::vector<target_vd> possible_vds() const;

    precision_roll dodge(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator) const;
    precision_roll parry_with(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator, ability::ability_enum parry_ability) const;
    precision_roll defend_with_value(target_vd vd, unsigned int vd_value);

  private:
    pre_precision_defense_declaration(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class precision_roll : public combat_step
  {
    friend class post_precision_defense_declaration;
    friend class pre_precision_defense_declaration;
    friend class attack_declaration;
    friend class vd_application;
    friend class outcome;

  public:

    precision_roll& precision(unsigned int precision_dice);
    precision_roll& precision(attribute::attribute_enum attribute, const ability::ability_name& ability);
    precision_roll& precision(attribute::attribute_enum attribute, const ability::ability_name& ability, const std::string& specialisation);
    precision_roll& bonus(unsigned int bonus_successes);
    precision_roll& malus(unsigned int malus_successes);
    precision_roll& internal_bonus(unsigned int internal_bonus_dice);
    precision_roll& internal_malus(unsigned int internal_malus_dice);
    precision_roll& target(body_target target);
    precision_roll& do_not_target();

    unsigned int pool() const;
    int external_bonus() const;

    vd_application apply(std::shared_ptr<dice::abstract_dice_roller> dice_roller);
    vd_application with_successes(unsigned int successes);
    post_precision_defense_declaration apply_and_defend(std::shared_ptr<dice::abstract_dice_roller> dice_roller);
    post_precision_defense_declaration with_successes_and_defend(unsigned int successes);

  private:
    precision_roll(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }

    void apply_roll(std::shared_ptr<dice::abstract_dice_roller> dice_roller);
  };

  class vd_application : public combat_step
  {
    friend class precision_roll;
    friend class post_precision_defense_declaration;

  public:
    bool hits() const;
    outcome on_fail() const;
    raw_damage_and_position_computation on_success() const;

    vd_application& bonus(unsigned int bonus_successes);
    vd_application& malus(unsigned int malus_successes);

  private:
    vd_application(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class outcome
  {
    friend class vd_application;
    friend class raw_damage_and_position_computation;
    friend class post_soak_damage;
    friend class final_damage;

  public:
    bool counter_available() const;
    unsigned int final_damage() const;
    unsigned int vd_penalty_on_attacker() const;
    unsigned int meters_pushed() const;
    body_target target_hit() const;

    bool was_hit() const;
    bool was_pushed() const;
    bool was_knocked_down() const;

  private:

    outcome()
      : _target(body_target::NO_TARGET),
        _hit(false), _pushed(false), _knocked(false), _can_counter(false),
        _final_damage(0), _action_penalty(0), _meters_pushed(0)
    { }

    body_target _target;
    bool _hit, _pushed, _knocked, _can_counter;
    unsigned int _final_damage, _action_penalty, _meters_pushed;
  };

  class raw_damage_and_position_computation : public combat_step
  {
    friend class vd_application;

  public:
    raw_damage_and_position_computation& base_damage(unsigned int basedamage);
    raw_damage_and_position_computation& min_damage(unsigned int basedamage);
    raw_damage_and_position_computation& damage_type(damage_type_enum damage_type);
    raw_damage_and_position_computation& attribute(unsigned int attribute_value);
    raw_damage_and_position_computation& drill(unsigned int weapon_drill);

    // target is automatically rolled if it wasn't set in the precision roll
    body_target target() const;
    bool passes(unsigned int soak, unsigned int armored_soak = 0) const;
    bool passes(const calculator::derived_value_calculator& calculator) const;
    outcome on_fail() const;
    post_soak_damage on_pass(unsigned int soak, unsigned int armored_soak = 0) const;
    post_soak_damage on_pass(const calculator::derived_value_calculator& calculator) const;

  private:
    void compute_post_soak_pool(unsigned int soak, unsigned int armored_soak = 0) const;
    void compute_post_soak_pool(const calculator::derived_value_calculator& calculator) const;
    raw_damage_and_position_computation(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class post_soak_damage : public combat_step
  {
    friend class raw_damage_and_position_computation;

  public:
    bool passes (unsigned int hardness) const;
    bool passes(const calculator::derived_value_calculator& calculator) const;
    outcome on_fail() const;
    post_hardness_damage on_pass() const;

  private:
    post_soak_damage(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }

  };

  class post_hardness_damage : public combat_step
  {
    friend class post_soak_damage;
  public:
    final_damage with_roll(unsigned int rolled_damage);
    final_damage roll(std::shared_ptr<dice::abstract_dice_roller> dice_roller);

  private:
    post_hardness_damage(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class final_damage : public combat_step
  {
    friend class post_hardness_damage;

  public:
    final_damage& knockback_meters(unsigned int successes);
    final_damage& knockdown(unsigned int successes);
    final_damage& with_balance(unsigned int balance);

    unsigned int damage() const;
    outcome end_attack() const;

  private:
    final_damage(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }  };

}

#endif // PHYSICAL_ATTACK_H
