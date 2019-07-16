#include "abilities/ability.h"

#include "json_constants.h"
#include "abilities/ability_names.h"

namespace character {

  ability::ability() : _name(ability_names::ability_declination::NO_DECLINATION), _value(0) {};

  ability::ability(const std::string& name, unsigned int value) : _name(name), _value(value) {}

  ability::ability(const ability& o) : _name(o._name), _value(o._value) { }

  ability& ability::operator=(const ability& o)
  {
    _name = o._name;
    _value = o._value;

    return *this;
  }

  ability::operator unsigned int() const
  {
    return _value;
  }

  ability::operator std::string() const
  {
    return _name;
  }

  std::string ability::get_name() const
  {
    return _name;
  }

  std::string ability::get_value() const
  {
    return std::to_string(_value);
  }

  unsigned int ability::get_ability_value() const
  {
    return _value;
  }

  void ability::set_value(unsigned int new_value)
  {
    _value = new_value;
  }

  void ability::serialisation()
  {
    synch(serialisation::json_constants::SLOT_VALUE, _value);
    synch(serialisation::json_constants::SLOT_NAME, _name);
  }

  bool ability::operator==(const ability& other) const
  {
    return _name == other._name && _value == other._value;
  }

}
