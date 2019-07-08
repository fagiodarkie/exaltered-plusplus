#include "abilities/specialisation.h"

#include "json_constants.h"

namespace character {
  specialisation::specialisation(const QString& name, unsigned int initial_value)
    : name(name), value(initial_value) {};

  specialisation::specialisation(const specialisation& o) : name(o.name), value(o.value) { }

  specialisation& specialisation::operator=(const specialisation& o)
  {
    name = o.name;
    value = o.value;

    return *this;
  }

  QString specialisation::get_name() const
  {
    return name;
  }

  QString specialisation::get_value() const
  {
    return QString::number(value);
  }

  unsigned int specialisation::get_specialisation_value() const
  {
    return value;
  }

  void specialisation::set_value(unsigned int new_value)
  {
    value = new_value;
  }

  void specialisation::read_from_json(const QJsonObject &json)
  {
    value = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_VALUE].toString().toInt());
    name = json[serialisation::json_constants::SLOT_NAME].toString();
  }

  void specialisation::write_to_json(QJsonObject &json) const
  {
    json[serialisation::json_constants::SLOT_VALUE] = QString::number(value);
    json[serialisation::json_constants::SLOT_NAME] = name;
  }

  bool specialisation::operator==(const specialisation& other) const
  {
    return name == other.name && value == other.value;
  }
}
