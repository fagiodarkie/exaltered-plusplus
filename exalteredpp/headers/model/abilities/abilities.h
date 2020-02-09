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
    //typedef reverse_ability_iterator<ability, map_type> reverse_iterator;
    //typedef reverse_ability_iterator<const ability, const map_type> const_reverse_iterator;

    iterator begin() { return iterator(_abilities, _abilities[iterator::FIRST_ABILITY].begin()); }
    iterator end() { return iterator(_abilities, _abilities[iterator::LAST_ABILITY].end()); }

    const_iterator begin() const { return const_iterator(_abilities, _abilities.at(iterator::FIRST_ABILITY).begin()); }
    const_iterator end()   const { return const_iterator(_abilities, _abilities.at(iterator::LAST_ABILITY).end()); }

    //iterator begin() { return iterator(_abilities, _abilities[iterator::FIRST_ABILITY].begin()); }
    //iterator end() { return iterator(_abilities, _abilities[iterator::LAST_ABILITY].end()); }
    //
    //iterator begin() { return iterator(_abilities, _abilities[iterator::FIRST_ABILITY].begin()); }
    //iterator end() { return iterator(_abilities, _abilities[iterator::LAST_ABILITY].end()); }

    virtual void serialisation() override;

    ability get(const ability_name& ab) const;
    ability& operator[](const ability_name& ab);

    ability get(ability_enum ab) const;
    ability& operator[](ability_enum ab);

    bool has(const ability_name& name) const;
    void add(ability&& ability);
    void add(const ability& ability);
    void remove(const ability_name& ability);

    unsigned long long size() const { return _abilities.size(); }

    abilities with_type(ability_enum ability_type) const;

    std::vector<ability_name> keys() const;

    virtual ~abilities() = default;

  private:

    map_type _abilities;


  };
}
