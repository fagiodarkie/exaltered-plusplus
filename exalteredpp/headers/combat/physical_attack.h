#ifndef PHYSICAL_ATTACK_H
#define PHYSICAL_ATTACK_H

#include "attack_defines.h"
#include "weapon.h"
#include <vector>

#include "character.h"
#include "derived_value_calculator.h"

namespace combat {

  class attack_declaration;
  class defense_declaration;
  class precision_roll;
  class vd_application;
  class raw_damage_and_position_computation;
  class post_soak_damage;
  class post_hardness_damage;
  class outcome;

  class combat_step {
  protected:
    struct attack_descriptor
    {
      unsigned int action_penalty;
      weapon weapon;
      std::vector<attack_attribute> attack_attributes;
      std::shared_ptr<character::character> attacker, defender;
      target_vd vd;

      int
      // info for attacker
      vd_value,
      vd_balance,
      precision_external_bonus,
      precision_external_malus,
      precision_internal_bonus,
      precision_internal_malus,
      soak,
      armor_soak,

      // info for defender
      precision_roll_result,
      bonus_damage,

      // info for everybody
      precision_dice,
      raw_damage_dice,
      post_soak_damage,
      post_hardness_damage,
      final_damage_dice,
      final_damage_result,
      final_damage_reduction,
      final_damage_multiplier;

      bool
      has_fixed_result,
      precision_rolled,
      damage_rolled,
      body_part_rolled;

      body_target target;
    };

    combat_step(std::shared_ptr<attack_descriptor> atk) : _atk(atk) { }
    std::shared_ptr<attack_descriptor> _atk;
  };

  class attack_declaration : combat_step
  {
    friend class precision_roll;
    friend class defense_declaration;

  public:
    static attack_declaration declare();
    static attack_declaration declare_as(std::initializer_list<attack_attribute> attributes);

    attack_declaration& is(std::initializer_list<attack_attribute> attributes);
    attack_declaration& is(attack_attribute attribute);
    attack_declaration& is_not(attack_attribute attribute);
    attack_declaration& with(const weapon& w);
    attack_declaration& with_action_penalty(unsigned int vd_penalty);
    attack_declaration& attacker(std::shared_ptr<character::character> attacker);

    defense_declaration declared() const;

  private:

    attack_declaration() : combat_step (std::make_shared<attack_descriptor>()) { }
  };

  class defense_declaration : combat_step
  {
    friend class attack_declaration;

  public:
    std::vector<target_vd> possible_vds() const;

    precision_roll dodge(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator) const;
    precision_roll parry_with(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator, ability::ability_enum parry_ability) const;
    precision_roll defend_with_value(target_vd vd, unsigned int vd_value, unsigned int vd_balance);

  private:
    defense_declaration(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class precision_roll : combat_step
  {
    friend class defense_declaration;
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
    precision_roll& with_successes(unsigned int successes);
    precision_roll& target(body_target target);
    precision_roll& do_not_target();

    unsigned int pool() const;
    int external_bonus() const;

    vd_application apply();

  private:
    precision_roll(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class vd_application : combat_step
  {
    friend class precision_roll;

  public:
    bool hits() const;
    outcome on_fail() const;
    raw_damage_and_position_computation on_success() const;

    vd_application& bonus(unsigned int bonus_successes);
    vd_application& malus(unsigned int malus_successes);

  private:
    vd_application(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class outcome : combat_step
  {
    friend class vd_application;
    friend class raw_damage_and_position_computation;
    friend class post_soak_damage;
    friend class post_hardness_damage;

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
    body_target _target;
    bool _hit, _pushed, _knocked, _can_counter;
    unsigned int _final_damage, _action_penalty, _meters_pushed;
  };

  class raw_damage_and_position_computation : combat_step
  {
    friend class vd_application;

  public:
    raw_damage_and_position_computation& base_damage(unsigned int basedamage);
    raw_damage_and_position_computation& min_damage(unsigned int basedamage);
    raw_damage_and_position_computation& attribute(unsigned int attribute_value);
    raw_damage_and_position_computation& attribute(attribute::attribute_enum attr, const character::character& c);
    raw_damage_and_position_computation& drill(unsigned int weapon_drill);

    // target is automatically rolled if it wasn't set in the precision roll
    body_target target() const;
    bool passes(unsigned int soak, unsigned int armored_soak = 0) const;
    bool passes(const character::character& c, const calculator::derived_value_calculator& calculator) const;
    outcome on_fail() const;
    post_soak_damage on_pass(unsigned int soak, unsigned int armored_soak = 0) const;
    post_soak_damage on_pass(const character::character& c, const calculator::derived_value_calculator& calculator) const;

  private:
    raw_damage_and_position_computation(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

  class post_soak_damage : combat_step
  {
    friend class raw_damage_and_position_computation;

  public:
    bool passes (unsigned int hardness) const;
    bool passes(const character::character& c, const calculator::derived_value_calculator& calculator) const;
    outcome on_fail() const;
    post_hardness_damage on_pass(unsigned int hardness) const;
    post_hardness_damage on_pass(const character::character& c, const calculator::derived_value_calculator& calculator) const;

  private:
    post_soak_damage(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }

  };

  class post_hardness_damage : combat_step
  {
    friend class post_soak_damage;
  public:
    outcome roll() const;

  private:
    post_hardness_damage(std::shared_ptr<attack_descriptor> atk) : combat_step(atk) { }
  };

}

#endif // PHYSICAL_ATTACK_H
