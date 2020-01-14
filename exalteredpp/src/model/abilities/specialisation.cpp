#include "abilities/specialisation.h"

#include "json_constants.h"

namespace ability {
  specialisation::specialisation(const std::string& name, unsigned int initial_value)
    : name(name), value(initial_value) {};

  specialisation::specialisation(const specialisation& o) : name(o.name), value(o.value) { }

  specialisation& specialisation::operator=(const specialisation& o)
  {
    name = o.name;
    value = o.value;

    return *this;
  }

  std::string specialisation::get_name() const
  {
    return name;
  }

  std::string specialisation::get_value() const
  {
    return std::to_string(value);
  }

  unsigned int specialisation::get_specialisation_value() const
  {
    return value;
  }

  void specialisation::set_value(unsigned int new_value)
  {
    value = new_value;
  }

  void specialisation::serialisation()
  {
    synch(serialisation::json_constants::SLOT_VALUE, value);
    synch(serialisation::json_constants::SLOT_NAME, name);
  }

  bool specialisation::operator==(const specialisation& other) const
  {
    return name == other.name && value == other.value;
  }
}
