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
    _atk->vd = target_vd::PHYSICAL_DODGE;
    auto vd = calculator.compute_physical_vd(*c, ability::ability_enum::MELEE);
    _atk->vd_value = vd.dodge_vd;
    _atk->vd_balance = vd.dodge_balance;

    return precision_roll(_atk);
  }

  precision_roll defense_declaration::parry_with(std::shared_ptr<character::character> c, const calculator::derived_value_calculator& calculator, ability::ability_enum parry_ability) const
  {
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
}
