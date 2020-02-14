#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "json_constants.h"
#include <numeric>

namespace ability {

  abilities::abilities()
  {
    for (auto ab_enum : ABILITIES)
      _abilities[ab_enum] = std::vector<ability>();
  }

  void abilities::serialisation()
  {
    if (saving())
      {
        std::vector<ability> ab_vector;
        for (auto abv: ABILITIES)
          for (auto ab: _abilities[abv])
            ab_vector.push_back(ab);
        synch(serialisation::json_constants::SLOT_ABILITIES, ab_vector);
      }
    else
      {
        _abilities.clear();
        std::vector<ability> ab_vector;
        synch(serialisation::json_constants::SLOT_ABILITIES, ab_vector);
        for (auto ab: ab_vector)
          add(ab);
      }
  }

  unsigned int abilities:: size() const
  {
    return std::accumulate(_abilities.begin(), _abilities.end(), 0U, [](unsigned int sum, std::pair<ability_enum, std::vector<ability>> pair)
      {
        return sum + pair.second.size();
      });
  }

  bool abilities::has(const ability_name &name) const
  {
    if (_abilities.find(name.ability_type) != _abilities.end())
      return _find_in_vector(_abilities.at(name.ability_type), name.subability) != _abilities.at(name.ability_type).end();
    return false;
  }

  ability abilities::get(const ability_name& ab) const
  {
    if (!has(ab))
      return ability();

    return *_find(ab);
  }

  std::vector<ability> abilities::with_type(ability_enum ability_type) const
  {
    return _abilities.at(ability_type);
  }

  ability& abilities::operator[](const ability_name& ab)
  {
    if (!has(ab))
      add(ability(ab));

    return *_get(ab);
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
    for (auto ab: _abilities)
      std::transform(ab.second.begin(), ab.second.end(), std::back_inserter(result), ability_name_getter);
    return result;
  }

  void abilities::add(const ability& ability)
  {
    if (has(ability.name()))
      return;

    _insert_in_vector(_abilities[ability.name().ability_type], ability);
  }

  void abilities::add(ability&& ability)
  {
    add(ability);
  }

  void abilities::remove(const ability_name& ability)
  {
    if (!has(ability))
      return;

    _remove_from_vector(_abilities[ability.ability_type], ability.subability);
  }


  abilities::const_iter_type abilities::_find(const ability_name& ab) const
  {
    return _find_in_vector(_abilities.at(ab.ability_type), ab.subability);
  }

  abilities::iter_type abilities::_get(const ability_name& ab)
  {
    return _get_in_vector(_abilities[ab.ability_type], ab.subability);
  }

  abilities::const_iter_type abilities::_find_in_vector(const std::vector<ability>& v, const std::string& name) const
  {
    return _find_in_vector(v, name, 0, v.size());
  }

  abilities::const_iter_type abilities::_find_in_vector(const std::vector<ability>& v, const std::string& name, int start, int end) const
  {
    if (start >= end)
      return v.end();

    int q = (start + end) / 2;
    if (v.at(q).name().subability == name)
      return v.begin() + q;

    if (v.at(q).name().subability < name)
      return _find_in_vector(v, name, start, q);

    return _find_in_vector(v, name, q + 1, end);
  }

  abilities::iter_type abilities::_get_in_vector(std::vector<ability>& v, const std::string& name) const
  {
    return _get_in_vector(v, name, 0, v.size());
  }

  abilities::iter_type abilities::_get_in_vector(std::vector<ability>& v, const std::string& name, int start, int end) const
  {
    if (start == end)
      return v.end();

    int q = (start + end) / 2;
    if (v.at(q).name().subability == name)
      return v.begin() + q;

    if (v.at(q).name().subability > name)
      return _get_in_vector(v, name, start, q);

    return _get_in_vector(v, name, q + 1, end);
  }

  void abilities::_insert_in_vector(std::vector<ability>& v, const ability& new_ability)
  {
    if (v.empty())
      {
        v.push_back(new_ability);
        return;
      }

    int start = 0, end = v.size();
    while (start != end)
      {
        int mid = (start + end) / 2;
        if (v[mid].name() == new_ability.name())
          {
            v[mid] = new_ability;
            return;
          }

        if (start == end - 1)
          break;

        if (ability_order_comparison(v[mid], new_ability))
          start = mid;
        else
          end = mid;
      }
    v.insert(v.begin() + start, new_ability);

  }

  void abilities::_remove_from_vector(std::vector<ability>& v, const std::string& name)
  {
    auto pos = _get_in_vector(v, name);
    if (pos != v.end())
      v.erase(pos);
  }

}
