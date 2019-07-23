#include "attributes/attribute.h"
#include "serialisation/json_constants.h"

namespace character
{
  attribute::attribute(std::string name) : _value(0), _name(name) {}

  attribute::attribute(std::string name, int value) : _value(value), _name(name) {}

  attribute::operator int() const
  {
    return _value;
  }

  std::string attribute::get_value() const
  {
    return std::to_string(_value);
  }

  attribute::operator std::string() const
  {
    return _name;
  }

  std::string attribute::get_name() const
  {
    return _name;
  }

  void attribute::serialisation()
  {
    synch(serialisation::json_constants::SLOT_VALUE, _value);
    synch(serialisation::json_constants::SLOT_NAME, _name);
  }
}
