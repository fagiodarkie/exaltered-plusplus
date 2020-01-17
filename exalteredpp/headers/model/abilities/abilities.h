#pragma once

#include <vector>
#include "../thirdparty/serialisable/serialisable.hpp"
#include "ability.h"
#include "ability_names.h"

namespace ability
{
  class abilities : public Serialisable
  {

  public:

    typedef std::vector<ability>::iterator iterator;
    typedef std::vector<ability>::const_iterator const_iterator;
    iterator begin() { return _abilities.begin(); }
    iterator end() { return _abilities.end(); }
    const_iterator begin() const { return _abilities.begin(); }
    const_iterator end() const { return _abilities.end(); }

    virtual void serialisation() override;

    ability get(const ability_name& ab) const;
    ability& operator[](const ability_name& ab);

    ability get(ability_enum ab) const;
    ability& operator[](ability_enum ab);

    bool has(const ability_name& name) const;
    void add(ability&& ability);
    void remove(const ability_name& ability);

    unsigned long long size() const { return _abilities.size(); }

    abilities with_type(ability_enum ability_type) const;

    std::vector<ability_name> keys() const;

    virtual ~abilities() = default;

  private:

    std::vector<ability> _abilities;
  };
}
