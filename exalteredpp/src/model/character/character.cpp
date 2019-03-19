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

  QString character::get_name() const
  {
    return _name;
  }

  void character::set_name(const QString& new_name)
  {
    _name = new_name;
    emit data_changed();
  }

  attribute character::get_attribute(attribute_name name) const
  {
    return _attributes.at(name);
  }

  void character::set_attribute(attribute_name name, attribute attribute)
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
