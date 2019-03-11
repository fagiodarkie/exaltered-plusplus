#include "character/character.h"
#include "json_constants.h"

using serialisation::json_constants;

namespace character
{
  character::character(QString name) : _name(name) { };

  character::character(const QJsonObject& object)
  {
    read(object);
  }

  QString character::getName() const
  {
    return _name;
  }

  attribute character::getAttribute(attribute_name name) const
  {
    return _attributes.at(name);
  }

  void character::setAttribute(attribute_name name, attribute attribute)
  {
    _attributes.emplace(name, attribute);
  }

  void character::read(const QJsonObject &object)
  {
    _name = object[json_constants::SLOT_NAME].toString();
  }

  void character::write(QJsonObject &object) const
  {
    object[json_constants::SLOT_NAME] = _name;
  }
}
