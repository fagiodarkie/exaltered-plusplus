#include "attributes/attribute.h"

namespace character
{
  attribute::attribute(QString name) : _value(0), _name(name) {}

  attribute::attribute(QString name, int value) : _value(value), _name(name) {}

  attribute::operator int() const
  {
    return _value;
  }

  attribute::operator QString() const
  {
    return _name;
  }
}
