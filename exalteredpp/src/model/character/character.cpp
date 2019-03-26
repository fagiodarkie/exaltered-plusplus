#include "character/character.h"
#include "json_constants.h"

using serialisation::json_constants;

namespace character
{
  character::character(QString name) : _name(name)
  {
    set_attribute(STRENGTH,     attribute(ATTRIBUTE_NAME.value(STRENGTH),     2));
    set_attribute(DEXTERITY,    attribute(ATTRIBUTE_NAME.value(DEXTERITY),    3));
    set_attribute(CONSTITUTION, attribute(ATTRIBUTE_NAME.value(CONSTITUTION), 2));
    set_attribute(CHARISMA,     attribute(ATTRIBUTE_NAME.value(CHARISMA),     2));
    set_attribute(MANIPULATION, attribute(ATTRIBUTE_NAME.value(MANIPULATION), 3));
    set_attribute(APPEARANCE,   attribute(ATTRIBUTE_NAME.value(APPEARANCE),   2));
    set_attribute(INTELLIGENCE, attribute(ATTRIBUTE_NAME.value(INTELLIGENCE), 3));
    set_attribute(PERCEPTION,   attribute(ATTRIBUTE_NAME.value(PERCEPTION),   2));
    set_attribute(WITS,         attribute(ATTRIBUTE_NAME.value(WITS),         3));
  };

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
    _attributes.read(object[json_constants::SLOT_ATTRIBUTES].toObject());
  }

  void character::write(QJsonObject &object) const
  {
    object[json_constants::SLOT_NAME] = _name;
    QJsonObject attributes_object;
    _attributes.write(attributes_object);
    object[json_constants::SLOT_ATTRIBUTES] = attributes_object;
  }
}
