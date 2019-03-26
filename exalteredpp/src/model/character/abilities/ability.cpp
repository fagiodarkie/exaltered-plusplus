#include "abilities/ability.h"

namespace character {

  ability::ability(const QString& name, int value) : _name(name), _value(value) {}

  ability::operator int() const
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

}
