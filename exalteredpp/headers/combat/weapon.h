#ifndef WEAPON_H
#define WEAPON_H

#include "attack_defines.h"
#include "action_defines.h"
#include <map>
#include <vector>
#include "attributes/attribute_names.h"
#include "abilities/ability_names.h"

namespace equip {
  using combat::damage_type_enum;
  using combat::action_speed;
  using combat::attack_attribute;
  class weapon
  {

  public:
    weapon(const std::string& name = "");

    std::string name() const;
    int precision_bonus() const;
    int base_damage() const;
    int defense() const;
    int IM() const;
    unsigned short int minimum_damage() const;
    unsigned short int drill() const;
    float range() const;
    damage_type_enum damage_type() const;
    bool can_be_used_with(ability::ability_enum ability) const;
    bool is(attack_attribute attribute) const;
    bool requires_minimum_for(attribute::attribute_enum attribute) const;
    unsigned short int minimum_for(attribute::attribute_enum attribute) const;
    attribute::attribute_enum precision_attribute() const;
    attribute::attribute_enum damage_attribute() const;
    action_speed speed_range() const;
    unsigned short int attack_ticks() const;
    std::vector<ability::ability_enum> relevant_abilities() const;

    weapon& with_precision(int precision);
    weapon& with_defense(int defense);
    weapon& with_im(int im);
    weapon& with_base_damage(int base_damage);
    weapon& with_damage_type(damage_type_enum damage_type);
    weapon& with_drill(unsigned short int drill);
    weapon& with_min_damage(unsigned short int min);
    weapon& with_range(float range);
    weapon& requires_attribute(attribute::attribute_enum attribute, unsigned short int minimum = 1);
    weapon& does_not_require(attribute::attribute_enum attribute);
    weapon& with(attack_attribute attribute);
    weapon& use_with(ability::ability_enum ability);
    weapon& do_not_use_with(ability::ability_enum ability);
    weapon& attacks_in_tempo(action_speed tempo);
    weapon& with_name(const std::string& name);
    weapon& requires_for_precision(attribute::attribute_enum precision_attribute);
    weapon& uses_for_damage(attribute::attribute_enum damage_attribute);

  private:

    std::string _name;
    damage_type_enum _damage_type;
    int _precision_bonus, _defense_bonus, _base_damage, _im_bonus;
    unsigned short int  _drill, _min_damage;
    float _range;
    std::map<attribute::attribute_enum, unsigned short int> _minimums;
    std::vector<ability::ability_enum> _possible_abilities;
    attribute::attribute_enum _precision_attribute, _damage_attribute;
    std::vector<attack_attribute> _weapon_attributes;
    action_speed _attack_speed;
  };
}

#endif // WEAPON_H
