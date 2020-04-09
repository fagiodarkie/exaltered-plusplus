#include "equipment/weapon.h"

#include "common/reverse_search.h"

namespace equipment {
  weapon::weapon(const std::string& name)
    : _name(name)
  {

  }

  std::string weapon::name() const
  {
    return _name;
  }

  int weapon::precision_bonus(attack_type a_type) const
  {
    return _project.precision_bonus(a_type);
  }

  int weapon::base_damage(attack_type a_type) const
  {
    return _project.base_damage(a_type);
  }

  int weapon::defense() const
  {
    return _project.defense();
  }

  int weapon::IM(attack_type a_type) const
  {
    return _project.IM(a_type);
  }

  unsigned short int weapon::minimum_damage(attack_type a_type) const
  {
    return _project.minimum_damage(a_type);
  }

  unsigned short int weapon::drill(attack_type a_type) const
  {
    return _project.drill(a_type);
  }

  float weapon::range(attack_type a_type) const
  {
    return _project.range(a_type);
  }

  damage_type_enum weapon::damage_type(attack_type a_type) const
  {
    return _project.damage_type(a_type);
  }

  bool weapon::can_be_used_with(ability::ability_name ability) const
  {
    return _project.can_be_used_with(ability);
  }

  bool weapon::is(attack_attribute attribute) const
  {
    return _project.is(attribute);
  }

  bool weapon::requires_minimum_for(attribute::attribute_enum attribute) const
  {
    return _project.requires_minimum_for(attribute);
  }

  unsigned short int weapon::minimum_for(attribute::attribute_enum attribute) const
  {
    return _project.minimum_for(attribute);
  }

  attribute::attribute_enum weapon::precision_attribute(attack_type a_type) const
  {
    return _project.precision_attribute(a_type);
  }

  attribute::attribute_enum weapon::damage_attribute(attack_type a_type) const
  {
    return _project.damage_attribute(a_type);
  }

  std::vector<ability::ability_name> weapon::relevant_abilities() const
  {
    return _project._possible_abilities();
  }
}
