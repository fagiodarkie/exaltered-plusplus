#ifndef WEAPON_H
#define WEAPON_H

#include "combat/attack_defines.h"
#include <map>
#include <vector>
#include "attributes/attribute_names.h"
#include "abilities/ability_names.h"
#include "craft/weapon_project.h"
#include "craft/material.h"
#include "craft/improvement.h"

namespace equipment {
  using combat::damage_type_enum;
  using combat::attack_attribute;
  using craft::attack_type;

  class weapon
  {

  public:
    weapon(const std::string& name = "");

    std::string name() const;
    int precision_bonus(attack_type = attack_type::DEFAULT) const;
    int base_damage(attack_type = attack_type::DEFAULT) const;
    int defense() const;
    int IM(attack_type = attack_type::DEFAULT) const;
    unsigned short int minimum_damage(attack_type = attack_type::DEFAULT) const;
    unsigned short int drill(attack_type = attack_type::DEFAULT) const;
    float range(attack_type = attack_type::DEFAULT) const;
    damage_type_enum damage_type(attack_type = attack_type::DEFAULT) const;
    bool can_be_used_with(ability::ability_name ability) const;
    bool is(attack_attribute attribute) const;
    bool requires_minimum_for(attribute::attribute_enum attribute) const;
    unsigned short int minimum_for(attribute::attribute_enum attribute) const;
    attribute::attribute_enum precision_attribute(attack_type = attack_type::DEFAULT) const;
    attribute::attribute_enum damage_attribute(attack_type = attack_type::DEFAULT) const;
    std::vector<ability::ability_name> relevant_abilities() const;

    weapon& with_project(const craft::weapon_project& project);
    weapon& with_material(const craft::material& material, unsigned int copies = 1);
    weapon& with_improvement(craft::improvement_enum new_improvement);

  private:

    std::string _name;
    craft::weapon_project _project;
    std::vector<craft::material> _materials;
    std::vector<craft::improvement_enum> _improvements;
  };
}

#endif // WEAPON_H
