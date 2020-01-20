#include "abilities/ability.h"

#include "json_constants.h"
#include "abilities/ability.h"
#include "abilities/ability_names.h"
#include "errors/ability_not_found_exception.h"

namespace ability {

  ability::ability() : _name(ability_enum::WAR, ability_declination::NO_DECLINATION), _value(0), _favourite(false) {};

  ability::ability(const ability_name& name, unsigned int value) : _name(name), _value(value), _favourite(false) {}

  ability::ability(const ability& o) : _name(o._name), _value(o._value), _favourite(o._favourite), _specialisations(o._specialisations) { }

  ability& ability::operator=(const ability& o)
  {
    _name = o._name;
    _value = o._value;
    _favourite = o._favourite;
    _specialisations = o._specialisations;

    return *this;
  }

  unsigned int ability::operator+(unsigned int other) const
  {
    return _value + other;
  }

  int ability::operator+(int other) const
  {
    return _value + other;
  }

  double ability::operator+(double other) const
  {
    return _value + other;
  }

  bool ability::operator<(const ability& other) const
  {
    return _value < other._value;
  }

  ability::operator unsigned int() const
  {
    return _value;
  }

  ability::operator std::string() const
  {
    return _name;
  }

  ability::operator ability_name() const
  {
    return _name;
  }

  ability_name ability::name() const
  {
    return _name;
  }

  unsigned int ability::value() const
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
    synch(serialisation::json_constants::SLOT_FAVOURITE, _favourite);
    synch(serialisation::json_constants::SLOT_SPECIALISATION, _specialisations);
  }

  bool ability::operator==(const ability& other) const
  {
    return _name == other._name && _value == other._value;
  }

  void ability::operator=(unsigned int new_value)
  {
    _value = new_value;
  }

  void ability::operator+=(unsigned int new_value)
  {
    _value += new_value;
  }

  void ability::operator-=(unsigned int new_value)
  {
    _value -= new_value;
  }

  void ability::operator++()
  {
    ++_value;
  }

  void ability::operator--()
  {
    --_value;
  }

  bool ability::favored() const
  {
    return _favourite;
  }

  void ability::set_favored(bool favored)
  {
    _favourite = favored;
  }

  bool ability::has(const std::string& specialisation_name) const
  {
    auto found_spec = std::find_if(_specialisations.begin(), _specialisations.end(), filter_specialisation_by_name(specialisation_name));

    return found_spec != _specialisations.end();
  }

  void ability::add(const class specialisation& new_specialisation)
  {
    set(new_specialisation.name(), new_specialisation.value());
  }

  void ability::add(std::string&& new_specialisation_name, unsigned int initial_value)
  {
    set(new_specialisation_name, initial_value);
  }

  void ability::set(const std::string& specialisation_name, unsigned int new_value)
  {
    if (!has(specialisation_name))
      _specialisations.emplace_back(::ability::specialisation(specialisation_name, new_value));

    std::find_if(_specialisations.begin(), _specialisations.end(), filter_specialisation_by_name(specialisation_name))->set_value(new_value);
  }

  void ability::increase(const std::string& specialisation_name, unsigned int add_value)
  {
    if (!has(specialisation_name))
      throw exception::ability_not_found_exception();

    get(specialisation_name).increase(add_value);
  }

  int ability::operator[](const std::string& specialisation_name) const
  {
    return _value + get(specialisation_name).value();
  }

  void ability::remove(const std::string& specialisation_to_remove)
  {
    _specialisations.erase(std::remove_if(_specialisations.begin(), _specialisations.end(), filter_specialisation_by_name(specialisation_to_remove)),
                           _specialisations.end());
  }

  std::vector<class specialisation> ability::specialisations() const
  {
    return _specialisations;
  }

  class specialisation ability::get(const std::string &name) const
  {
    if (!has(name))
      return ::ability::specialisation();
    return *std::find_if(_specialisations.begin(), _specialisations.end(), filter_specialisation_by_name(name));
  }

  class specialisation& ability::get(const std::string &name)
  {
    if (!has(name))
      set(name, 0);

    return *std::find_if(_specialisations.begin(), _specialisations.end(), filter_specialisation_by_name(name));
  }
}
