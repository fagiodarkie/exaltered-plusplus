#include "character/character.h"

namespace character
{
  character::character(QString name) : _name(name) { };

  QString character::getName() const
  {
    return _name;
  }

  void character::read(QJsonObject &object)
  {
    _name = object["name"].toString();
  }

  void character::write(QJsonObject &object) const
  {
    object["name"] = _name;
  }
}
