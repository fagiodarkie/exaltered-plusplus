#include "combat/weapon.h"

#include "common/reverse_search.h"

namespace combat {
  weapon::weapon(const std::string& name)
    : _name(name),
      _damage_type(damage_type_enum::BASHING),
      _precision_bonus(0),
      _defense_bonus(0),
      _base_damage(0),
      _im_bonus(0),
      _drill(0),
      _min_damage(0),
      _range(0),
      _precision_attribute(attribute::attribute_enum::DEXTERITY),
      _damage_attribute(attribute::attribute_enum::STRENGTH),
      _attack_speed(action_speed::ANDANTE)
  {

  }

  std::string weapon::name() const
  {
    return _name;
  }

  int weapon::precision_bonus() const
  {
    return _precision_bonus;
  }

  int weapon::base_damage() const
  {
    return _base_damage;
  }

  int weapon::defense() const
  {
    return _defense_bonus;
  }

  int weapon::IM() const
  {
    return _im_bonus;
  }

  unsigned short int weapon::minimum_damage() const
  {
    return _min_damage;
  }

  unsigned short int weapon::drill() const
  {
    return _drill;
  }

  float weapon::range() const
  {
    return _range;
  }

  damage_type_enum weapon::damage_type() const
  {
    return _damage_type;
  }

  bool weapon::can_be_used_with(ability::ability_enum ability) const
  {
    return commons::contains(_possible_abilities, ability);
  }

  bool weapon::is(attack_attribute attribute) const
  {
    return commons::contains(_weapon_attributes, attribute);
  }

  bool weapon::requires_minimum_for(attribute::attribute_enum attribute) const
  {
    return commons::find(_minimums, attribute) != _minimums.end();
  }

  unsigned short int weapon::minimum_for(attribute::attribute_enum attribute) const
  {
    return requires_minimum_for(attribute) ? _minimums.at(attribute) : 0;
  }

  attribute::attribute_enum weapon::precision_attribute() const
  {
    return _precision_attribute;
  }

  attribute::attribute_enum weapon::damage_attribute() const
  {
    return _damage_attribute;
  }

  action_speed weapon::speed_range() const
  {
    return _attack_speed;
  }

  unsigned short int weapon::attack_ticks() const
  {
    return static_cast<unsigned char>(_attack_speed) + _im_bonus;
  }

  std::vector<ability::ability_enum> weapon::relevant_abilities() const
  {
    return _possible_abilities;
  }

  weapon& weapon::with_precision(int precision)
  {
    _precision_bonus = precision;
    return *this;
  }

  weapon& weapon::with_defense(int defense)
  {
    _defense_bonus = defense;
    return *this;
  }

  weapon& weapon::with_im(int im)
  {
    _im_bonus = im;
    return *this;
  }

  weapon& weapon::with_base_damage(int base_damage)
  {
    _base_damage = base_damage;
    return *this;
  }

  weapon& weapon::with_damage_type(damage_type_enum damage_type)
  {
    _damage_type = damage_type;
    return *this;
  }

  weapon& weapon::with_drill(unsigned short int drill)
  {
    _drill = drill;
    return *this;
  }

  weapon& weapon::with_min_damage(unsigned short int min)
  {
    _min_damage = min;
    return *this;
  }

  weapon& weapon::with_range(float range)
  {
    _range = range;
    return *this;
  }

  weapon& weapon::requires_attribute(attribute::attribute_enum attribute, unsigned short int minimum)
  {
    _minimums[attribute] = minimum;
    return *this;
  }

  weapon& weapon::does_not_require(attribute::attribute_enum attribute)
  {
    if (requires_minimum_for(attribute))
      _minimums.erase(commons::find(_minimums, attribute));
    return *this;
  }

  weapon& weapon::with(attack_attribute attribute)
  {
    _weapon_attributes.push_back(attribute);
    return *this;
  }

  weapon& weapon::use_with(ability::ability_enum ability)
  {
    _possible_abilities.push_back(ability);
    return *this;
  }

  weapon& weapon::do_not_use_with(ability::ability_enum ability)
  {
    if (can_be_used_with(ability))
      _possible_abilities.erase(std::find(_possible_abilities.begin(), _possible_abilities.end(), ability));
    return *this;
  }

  weapon& weapon::attacks_in_tempo(action_speed tempo)
  {
    _attack_speed = tempo;
    return *this;
  }

  weapon& weapon::with_name(const std::string& name)
  {
    _name = name;
    return *this;
  }

  weapon& weapon::requires_for_precision(attribute::attribute_enum precision_attribute)
  {
    _precision_attribute = precision_attribute;
    return *this;
  }

  weapon& weapon::uses_for_damage(attribute::attribute_enum damage_attribute)
  {
    _damage_attribute = damage_attribute;
    return *this;
  }

}
