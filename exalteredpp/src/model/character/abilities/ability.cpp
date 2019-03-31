#include "abilities/ability.h"

#include "json_constants.h"
#include "abilities/ability_names.h"

namespace character {

  ability::ability() : _name(ability_declination::NO_DECLINATION), _value(0) {};

  ability::ability(const QString& name, unsigned int value) : _name(name), _value(value) {}

  ability::operator unsigned int() const
  {
    return _value;
  }

  ability::operator QString() const
  {
    return _name;
  }

  QString ability::get_name() const
  {
    return _name;
  }

  QString ability::get_value() const
  {
    return QString::number(_value);
  }

  unsigned int ability::get_ability_value() const
  {
    return _value;
  }

  void ability::set_value(unsigned int new_value)
  {
    _value = new_value;
  }

  void ability::read_from_json(const QJsonObject &json)
  {
    _value = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_VALUE].toInt());
    _name = json[serialisation::json_constants::SLOT_NAME].toString();
  }

  void ability::write_to_json(QJsonObject &json) const
  {
    json[serialisation::json_constants::SLOT_VALUE] = QString::number(_value);
    json[serialisation::json_constants::SLOT_NAME] = _name;
  }

  bool ability::operator==(const ability& other) const
  {
    return _name == other._name && _value == other._value;
  }

}
