#include "social/philosophy.h"

#include "serialisation/json_constants.h"

namespace character {
  namespace social {

    philosophy::philosophy(QString name, unsigned int value)
      : _value(value), _name(name) {}

    QString philosophy::name() const
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

    void philosophy::read_from_json(const QJsonObject &json)
    {
      _value = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_VALUE].toString().toInt());
      _name = json[serialisation::json_constants::SLOT_NAME].toString();
    }

    void philosophy::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_VALUE] = QString::number(_value);
      json[serialisation::json_constants::SLOT_NAME] = _name;
    }

    philosophy::~philosophy() {}
  }
}
