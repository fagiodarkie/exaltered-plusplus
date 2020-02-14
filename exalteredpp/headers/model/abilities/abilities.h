#pragma once

#include <vector>
#include "../thirdparty/serialisable/serialisable.hpp"
#include "ability.h"
#include "ability_names.h"
#include "abilities_iterator.h"

namespace ability
{
  class abilities : public Serialisable
  {

  private:
    typedef std::map<ability_enum, std::vector<ability>> map_type;
    typedef typename std::vector<ability>::iterator iter_type;
    typedef typename std::vector<ability>::const_iterator const_iter_type;

  public:

    typedef ability_iterator<ability, map_type, iter_type> iterator;
    typedef ability_iterator<ability, const map_type, const_iter_type> const_iterator;

    iterator begin() { return iterator(_abilities); }
    iterator end() {
      auto result = iterator(_abilities);
      result.ptr = result.map_ref.at(result._last_filled_ability()).end();
      return result;
    }

    const_iterator begin() const { return const_iterator(_abilities); }
    const_iterator end()   const {
      auto result = const_iterator(_abilities);
      result.ptr = result.map_ref.at(result._last_filled_ability()).end();
      return result;
    }

    abilities();
    virtual void serialisation() override;

    ability get(const ability_name& ab) const;
    ability& operator[](const ability_name& ab);

    ability get(ability_enum ab) const;
    ability& operator[](ability_enum ab);

    bool has(const ability_name& name) const;
    void add(ability&& ability);
    void add(const ability& ability);
    void remove(const ability_name& ability);

    unsigned int size() const;

    std::vector<ability> with_type(ability_enum ability_type) const;

    std::vector<ability_name> keys() const;

    virtual ~abilities() = default;

  private:

    map_type _abilities;

    void _insert_in_vector(std::vector<ability>& v, const ability& new_ability);
    void _remove_from_vector(std::vector<ability>& v, const std::string& name = ability_declination::NO_DECLINATION);
    const_iter_type _find(const ability_name& ab) const;
    iter_type _get(const ability_name& ab);
    const_iter_type _find_in_vector(const std::vector<ability>& v, const std::string& name = ability_declination::NO_DECLINATION) const;
    const_iter_type _find_in_vector(const std::vector<ability>& v, const std::string& name, int start, int end) const;
    iter_type _get_in_vector(std::vector<ability>& v, const std::string& name = ability_declination::NO_DECLINATION) const;
    iter_type _get_in_vector(std::vector<ability>& v, const std::string& name, int start, int end) const;

    ability_enum _first_filled_ability() const;
    ability_enum _last_filled_ability() const;
  };

}
