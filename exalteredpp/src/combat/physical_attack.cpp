#include "combat/physical_attack.h"

namespace combat {

  attack_declaration attack_declaration::declare()
  {
    return attack_declaration();
  }

  attack_declaration attack_declaration::declare_as(std::initializer_list<attack_attribute> attributes)
  {
    attack_declaration res;
    res._atk->attack_attributes = attributes;
    return res;
  }

  attack_declaration& attack_declaration::is(std::initializer_list<attack_attribute> attributes)
  {
    _atk->attack_attributes = attributes;
    return *this;
  }

  attack_declaration& attack_declaration::is(attack_attribute attribute)
  {
    if (!commons::contains(_atk->attack_attributes, attribute))
      _atk->attack_attributes.push_back(attribute);
    return *this;
  }

  attack_declaration& attack_declaration::is_not(attack_attribute attribute)
  {
    if (commons::contains(_atk->attack_attributes, attribute))
      _atk->attack_attributes.erase(std::find(_atk->attack_attributes.begin(), _atk->attack_attributes.end(), attribute));
    return *this;
  }

  attack_declaration& attack_declaration::with(const weapon& w)
  {
    _atk->weapon = w;
    return *this;
  }

  attack_declaration& attack_declaration::with_action_penalty(unsigned int vd_penalty)
  {
    _atk->action_penalty = vd_penalty;
    return *this;
  }

  attack_declaration& attack_declaration::attacker(std::shared_ptr<character::character> attacker)
  {
    _atk->attacker = attacker;
    return *this;
  }

  defense_declaration attack_declaration::declared() const
  {
    return defense_declaration (_atk);
  }

  std::vector<target_vd> defense_declaration::possible_vds() const
  {
    bool can_dodge = !(commons::contains(_atk->attack_attributes, attack_attribute::NON_DODGEABLE)),
        can_parry = !(commons::contains(_atk->attack_attributes, attack_attribute::NON_PARRYABLE));

    std::vector<target_vd> result;
    if (can_dodge) result.push_back(target_vd::PHYSICAL_DODGE);
    if (can_parry) result.push_back(target_vd::PHYSICAL_PARRY);

    return result;
  }

  precision_roll defense_declaration::dodge(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator) const
  {
    _atk->defender = c;
    _atk->vd = target_vd::PHYSICAL_DODGE;
    auto vd = calculator.compute_physical_vd(*c, ability::ability_enum::MELEE);
    _atk->vd_value = vd.dodge_vd;
    _atk->vd_balance = vd.dodge_balance;

    return precision_roll(_atk);
  }

  precision_roll defense_declaration::parry_with(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator, ability::ability_enum parry_ability) const
  {
    _atk->defender = c;
    _atk->vd = target_vd::PHYSICAL_PARRY;
    auto vd = calculator.compute_physical_vd(*c, parry_ability);
    _atk->vd_value = vd.parry_vd;
    _atk->vd_balance = vd.parry_balance;

    return precision_roll(_atk);
  }

  precision_roll defense_declaration::defend_with_value(target_vd vd, unsigned int vd_value, unsigned int vd_balance)
  {
    _atk->vd = vd;
    _atk->vd_value = vd_value;
    _atk->vd_balance = vd_balance;

    return precision_roll(_atk);
  }


  precision_roll& precision_roll::precision(unsigned int precision_dice)
  {
    _atk->precision_dice = precision_dice;
    return *this;
  }

  precision_roll& precision_roll::precision(attribute::attribute_enum attribute, const ability::ability_name& ability)
  {
    if (_atk->attacker)
      _atk->precision_dice = _atk->attacker->attribute(attribute) + _atk->attacker->get(ability);

    return *this;
  }

  precision_roll& precision_roll::precision(attribute::attribute_enum attribute, const ability::ability_name& ability, const std::string& specialisation)
  {
    if (_atk->attacker)
      _atk->precision_dice = _atk->attacker->attribute(attribute) + _atk->attacker->get(ability)[specialisation];

    return *this;
  }

  precision_roll& precision_roll::bonus(unsigned int bonus_successes)
  {
    _atk->precision_external_bonus = bonus_successes;
    return *this;
  }

  precision_roll& precision_roll::malus(unsigned int malus_successes)
  {
    _atk->precision_external_malus = malus_successes;
    return *this;
  }

  precision_roll& precision_roll::internal_bonus(unsigned int internal_bonus_dice)
  {
    _atk->precision_internal_bonus = internal_bonus_dice;
    return *this;
  }

  precision_roll& precision_roll::internal_malus(unsigned int internal_malus_dice)
  {
    _atk->precision_internal_malus = internal_malus_dice;
    return *this;
  }

  precision_roll& precision_roll::with_successes(unsigned int successes)
  {
    _atk->precision_rolled = true;
    _atk->precision_roll_result = successes;
    return *this;
  }

  precision_roll& precision_roll::target(body_target target)
  {
    _atk->target = target;
    _atk->body_part_rolled = true;
    return *this;
  }

  precision_roll& precision_roll::do_not_target()
  {
    _atk->target = body_target::NO_TARGET;
    _atk->body_part_rolled = false;
    return *this;
  }

  unsigned int precision_roll::pool() const
  {
    return _atk->precision_dice + _atk->precision_internal_bonus - _atk->precision_internal_malus;
  }

  int precision_roll::external_bonus() const
  {
    return _atk->precision_external_bonus - _atk->precision_external_malus;
  }

  vd_application precision_roll::apply()
  {
    if (!_atk->precision_rolled)
      {
        // todo roll precision
      }

    return vd_application(_atk);
  }

}
