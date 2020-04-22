#ifndef WEAPON_H
#define WEAPON_H

#include "combat/attack_defines.h"
#include <map>
#include <vector>
#include <functional>

#include "../thirdparty/serialisable/serialisable.hpp"
#include "attributes/attribute_names.h"
#include "abilities/ability_names.h"
#include "craft/weapon_project.h"
#include "craft/material.h"
#include "craft/improvement.h"

namespace equipment {
  using combat::damage_type_enum;
  using combat::attack_attribute;
  using craft::attack_type;

  class weapon : public Serialisable
  {

  public:

    static const unsigned short MAX_IMPROVEMENT_SLOT = 5;

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

    weapon& with_name(const std::string& name);
    weapon& with_project(const craft::weapon_project& project);
    weapon& remove_material(const std::string& material);
    weapon& with_material(const craft::material& material, unsigned int copies = 1);
    weapon& remove_improvement(craft::improvement_enum new_improvement);
    weapon& with_improvement(craft::improvement_enum new_improvement, unsigned int copies = 1);

    void serialisation() override;

  private:

    int material_bonus(std::function<int(int, const craft::material&)> accumulator) const;
    bool material_bonus_any(std::function<bool(bool, const craft::material&)> accumulator) const;

    static const std::function<int(int, const craft::material&)> sum_material_precision,
      sum_material_slots, sum_material_im, sum_material_defense, sum_material_drill, greater_material_min_damage;

    static const std::function<bool(bool, const craft::material&)> any_material_damage_override;

    static std::function<int(int, const craft::material&)> add_soak(damage_type_enum damage);
    static std::function<int(int, const craft::material&)> add_damage_bonus(damage_type_enum damage);

    std::string _name;
    craft::weapon_project _project;
    std::vector<craft::material> _materials;
    std::vector<craft::improvement_enum> _improvements;
  };
}

#endif // WEAPON_H
