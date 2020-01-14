#pragma once

#include <string>
#include "behavioral/name_value_pair.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace attribute
{
  class attribute : public model::name_value_pair, public Serialisable
  {
  public:
    attribute() = default;
    attribute(std::string name);
    attribute(std::string name, int value);

    std::string get_value() const override;
    std::string get_name() const override;
    void set_value(int new_value);

    virtual void serialisation() override;

    operator int() const;
    operator std::string() const;

  private:
    int _value;
    std::string _name;
  };
}
