#ifndef PHYSICAL_ATTACK_H
#define PHYSICAL_ATTACK_H

#include "attack_resolution/attack_defines.h"
#include <vector>

#include "character.h"
#include "derived_value_calculator.h"

namespace calculator {

  class attack_declaration;
  class defense_declaration;
  class precision_roll;
  class vd_application;
  class raw_damage_and_position_computation;
  class post_soak_damage;
  class post_hardness_damage;
  class damage_roll;
  class outcome;


  class attack_declaration {
    friend class precision_roll;
    friend class defense_declaration;

  public:
    static attack_declaration declare();
    static attack_declaration declare_as(std::initializer_list<attack_attribute> attributes);

    attack_declaration& is(damage_type type);
    attack_declaration& is(std::initializer_list<attack_attribute> attributes);
    attack_declaration& is(attack_attribute attribute);
    attack_declaration& is_not(attack_attribute attribute);
    attack_declaration& with_vd_penalty(unsigned int vd_penalty);

    defense_declaration declared() const;

  private:

    attack_declaration() { }

    unsigned int _vd_penalty;
    damage_type _type;
    std::vector<attack_attribute> _attributes;
  };

  class defense_declaration {
    friend class attack_declaration;

  public:
    std::vector<target_vd> possible_vds() const;

    precision_roll defend_with(target_vd vd, const character::character& c, const derived_value_calculator& calculator) const;
    precision_roll defend_with_value(target_vd vd, unsigned int vd_value);

  private:
    defense_declaration(const attack_declaration& attack);

    attack_declaration _attack;
  };

  class precision_roll
  {
    friend class defense_declaration;
    friend class vd_application;
    friend class outcome;

  public:

    precision_roll& precision(unsigned int precision_dice);
    precision_roll& precision(attribute::attribute_enum attribute, const ability::ability_name& ability, const character::character& c);
    precision_roll& precision(attribute::attribute_enum attribute, const ability::ability_name& ability, const std::string& specialisation, const character::character& c);
    precision_roll& bonus(unsigned int bonus_successes);
    precision_roll& malus(unsigned int malus_successes);
    precision_roll& internal_malus(unsigned int internal_malus_dice);
    precision_roll& with_successes(unsigned int successes);
    precision_roll& target(body_target target);
    precision_roll& do_not_target();

    unsigned int pool() const;
    unsigned int external_bonus() const;

    vd_application apply();

  private:
    precision_roll(const attack_declaration& attack, target_vd vd, unsigned int vd_value);

    attack_declaration _attack;
    target_vd _vd;
    unsigned int _vd_value, _precision_dice, _external_bonus, _external_malus, _internal_malus, _roll_result, _final_successes;
    bool _has_fixed_result, _rolled;
    body_target _target;
  };

  class vd_application {
    friend class precision_roll;

  public:
    bool hits() const;
    outcome on_fail() const;
    raw_damage_and_position_computation on_success() const;

    vd_application& bonus(unsigned int bonus_successes);
    vd_application& malus(unsigned int malus_successes);

  private:
    vd_application(const precision_roll& precision);

    precision_roll _precision;
    unsigned int _bonus, _malus;
  };

  class outcome {
    friend class vd_application;
    friend class raw_damage_and_position_computation;

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
    unsigned int _final_damage, _vd_penalty, _meters_push;
  };

  class raw_damage_and_position_computation {
    friend class vd_application;

  public:
    raw_damage_and_position_computation& base_damage(unsigned int basedamage);
    raw_damage_and_position_computation& attribute(unsigned int attribute_value);
    raw_damage_and_position_computation& attribute(attribute::attribute_enum attr, const character::character& c);
    raw_damage_and_position_computation& drill(unsigned int weapon_drill);

    // target is automatically rolled if it wasn't set in the precision roll
    body_target target() const;
    bool passes(unsigned int soak) const;
    bool passes(const character::character& c, const derived_value_calculator& calculator) const;
    outcome on_fail() const;
    post_soak_damage on_pass(unsigned int soak) const;
    post_soak_damage on_pass(const character::character& c, const derived_value_calculator& calculator) const;

  private:
    raw_damage_and_position_computation(const precision_roll& roll, unsigned int extra_successes);

    precision_roll _roll;
    unsigned int _extra_successes, _base_damage, _attribute_damage, _drill;
  };

}

#endif // PHYSICAL_ATTACK_H
