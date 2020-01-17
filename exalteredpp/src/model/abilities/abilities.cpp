#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "json_constants.h"

namespace ability {

  void abilities::serialisation()
  {
    synch(serialisation::json_constants::SLOT_ABILITIES, _abilities);
  }

  bool abilities::has(const ability_name &name) const
  {
    return std::find_if(_abilities.begin(), _abilities.end(), filter_ability_by_ability_name(name)) != _abilities.end();
  }

  ability abilities::get(const ability_name& ab) const
  {
    auto found_ability = std::find_if(_abilities.begin(), _abilities.end(), filter_ability_by_ability_name(ab));

    if (found_ability == _abilities.end())
      return ability();

    return *found_ability;
  }

  abilities abilities::with_type(ability_enum ability_type) const
  {
    abilities result;
    std::copy_if(_abilities.begin(), _abilities.end(), std::back_inserter(result._abilities), filter_ability_by_ability_type(ability_type));
    return result;
  }

  ability& abilities::operator[](const ability_name& ab)
  {
    if (!has(ab))
      add(ability(ab));

    return *std::find_if(_abilities.begin(), _abilities.end(), filter_ability_by_ability_name(ab));
  }

  ability  abilities::get(ability_enum ab) const
  {
    return get(ability_name(ab));
  }

  ability& abilities::operator[](ability_enum ab)
  {
    return (*this)[ability_name(ab)];
  }

  std::vector<ability_name> abilities::keys() const
  {
    std::vector<ability_name> result;
    std::transform(_abilities.begin(), _abilities.end(), std::back_inserter(result), ability_name_getter);
    return result;
  }

  void abilities::add(ability&& ability)
  {
    if (has(ability.name()))
      return;

    _abilities.emplace_back(ability);
    // keep the abilities sorted
    std::sort(_abilities.begin(), _abilities.end(), ability_order_comparison);
  }

  void abilities::remove(const ability_name& ability)
  {
    if (!has(ability))
      return;

    _abilities.erase(std::remove_if(_abilities.begin(), _abilities.end(), filter_ability_by_ability_name(ability)),
                     _abilities.end());
  }



}
