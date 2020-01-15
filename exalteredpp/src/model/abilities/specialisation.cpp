#include "abilities/specialisation.h"

#include "json_constants.h"

namespace ability {
  specialisation::specialisation(const std::string& name, unsigned int initial_value)
    : _name(name), _value(initial_value) {};

  specialisation::specialisation(const specialisation& o) : _name(o._name), _value(o._value) { }

  specialisation& specialisation::operator=(const specialisation& o)
  {
    _name  = o._name;
    _value = o._value;

    return *this;
  }

  std::string specialisation::name() const
  {
    return _name;
  }

  unsigned int specialisation::value() const
  {
    return _value;
  }

  void specialisation::set_value(unsigned int new_value)
  {
    _value = new_value;
  }

  void specialisation::serialisation()
  {
    synch(serialisation::json_constants::SLOT_VALUE, _value);
    synch(serialisation::json_constants::SLOT_NAME, _name);
  }

  bool specialisation::operator==(const specialisation& other) const
  {
    return _name == other._name && _value == other._value;
  }
}
