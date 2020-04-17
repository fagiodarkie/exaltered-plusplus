#include "equipment/weapon.h"

#include "common/reverse_search.h"
#include <numeric>

namespace equipment {

  int weapon::material_bonus(std::function<int (int, const craft::material &)> accumulator) const
  {
    return std::accumulate(_materials.begin(), _materials.end(), 0, accumulator);
  }

  bool weapon::material_bonus_any(std::function<bool (bool, const craft::material &)> accumulator) const
  {
    return std::accumulate(_materials.begin(), _materials.end(), false, accumulator);
  }

  const std::function<int(int, const craft::material&)> sum_material_precision = [](int s, const craft::material& material) {
    return s + material.precision_bonus();
  };

  const std::function<int(int, const craft::material&)> sum_material_im= [](int s, const craft::material& material) {
    return s + material.im_bonus();
  };

  const std::function<int(int, const craft::material&)> sum_material_defense= [](int s, const craft::material& material) {
    return s + material.defense_bonus();
  };

  const std::function<int(int, const craft::material&)> sum_material_drill = [](int s, const craft::material& material) {
    return s + material.drill_bonus();
  };

  const std::function<int(int, const craft::material&)> sum_material_slots = [](int s, const craft::material& material) {
    return s + material.slots_taken();
  };

  const std::function<int(int, const craft::material&)> greater_material_min_damage = [](int s, const craft::material& material) {
    return std::max(s, (int)material.minimum());
  };

  const std::function<bool(bool, const craft::material&)> any_material_damage_override = [](bool s, const craft::material& material) {
    return s || material.changes_damage_type();
  };

  std::function<int(int, const craft::material&)> weapon::add_soak(damage_type_enum damage)
  {
    return [damage](int s, const craft::material& material) {
        return s + material.soak(damage);
      };
  }

  std::function<int(int, const craft::material&)> weapon::add_damage_bonus(damage_type_enum damage)
  {
    return [damage](int s, const craft::material& material) {
        return s + material.damage_bonus(damage);
      };
  }

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
    return _project.precision_bonus(a_type) + material_bonus(sum_material_precision);
  }

  int weapon::base_damage(attack_type a_type) const
  {
    return _project.base_damage(a_type) + material_bonus(add_damage_bonus(_project.damage_type(a_type)));
  }

  int weapon::defense() const
  {
    return _project.defense() + material_bonus(sum_material_defense);
  }

  int weapon::IM(attack_type a_type) const
  {
    return _project.IM(a_type) + material_bonus(sum_material_im);
  }

  unsigned short int weapon::minimum_damage(attack_type a_type) const
  {
    return _project.minimum_damage(a_type) + material_bonus(greater_material_min_damage);
  }

  unsigned short int weapon::drill(attack_type a_type) const
  {
    return _project.drill(a_type) + material_bonus(sum_material_drill);
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
    return _project.relevant_abilities();
  }

  void weapon::serialisation()
  {

  }
}
