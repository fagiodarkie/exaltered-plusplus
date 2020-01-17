#include "social/philosophy.h"

#include "serialisation/json_constants.h"

namespace character {
  namespace social {

    philosophy::philosophy(std::string name, unsigned int value)
      : _value(value), _name(name) {}

    std::string philosophy::name() const
    {
      return _name;
    }

    unsigned int philosophy::value() const
    {
      return _value;
    }

    void philosophy::set_value(unsigned int new_value)
    {
      _value = new_value;
    }

    bool philosophy::operator== (const philosophy& o) const
    {
      return _name == o._name && _value == o._value;
    }

    void philosophy::serialisation()
    {
      synch(serialisation::json_constants::SLOT_VALUE, _value);
      synch(serialisation::json_constants::SLOT_NAME, _name);
    }

    philosophy::~philosophy() {}
  }
}
