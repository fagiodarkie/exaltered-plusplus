#pragma once

#include <string>
#include "../thirdparty/serialisable/serialisable.hpp"
#include "behavioral/name_value_pair.h"

namespace ability {
  class specialisation : public Serialisable
  {
  public:
    specialisation(const std::string& name = "", unsigned int initial_value = 1);
    specialisation(const specialisation& o);
    specialisation& operator=(const specialisation& o);

    std::string name() const;
    unsigned int value() const;

    void set_value(unsigned int new_value);

    virtual void serialisation() override;

    bool operator==(const specialisation& other) const;

    virtual ~specialisation() {}

  private:
    std::string _name;
    unsigned int _value;

  };
}
