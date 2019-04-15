#include "character/character.h"
#include "json_constants.h"

using serialisation::json_constants;

namespace character
{
  character::character(QString name, unsigned int id) : _name(name), _id(id) { };

  character::character(const QJsonObject& object)
  {
    read_from_json(object);
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

  character_type character::get_type() const
  {
    return _type;
  }

  void character::set_type(character_type type)
  {
    _type = type;
  }

  attribute character::get_attribute(attribute_names::attribute_name name) const
  {
    return _attributes.value(name);
  }

  void character::set_attribute(attribute_names::attribute_name name, attribute attribute)
  {
    _attributes.insert(name, attribute);
  }

  ability character::get_ability(ability_names::ability_name name, const QString& ability_declination) const
  {
    return _abilities.value(name).get_ability(ability_declination);
  }

  ability_group character::get_ability_group(ability_names::ability_name name) const
  {
    return _abilities.value(name);
  }

  void character::set_ability(ability_names::ability_name name, ability_group ability)
  {
    _abilities.insert(name, ability);
  }

  void character::read_from_json(const QJsonObject &object)
  {
    _name = object[json_constants::SLOT_NAME].toString();
    _id = static_cast<unsigned int>(object[json_constants::SLOT_ID].toInt());
    _attributes.read_from_json(object[json_constants::SLOT_ATTRIBUTES].toObject());
    _abilities.read_from_json(object[json_constants::SLOT_ABILITIES].toObject());
  }

  void character::write_to_json(QJsonObject &object) const
  {
    object[json_constants::SLOT_NAME] = _name;
    object[json_constants::SLOT_ID] = QString::number(_id);

    QJsonObject attributes_object;
    _attributes.write_to_json(attributes_object);
    object[json_constants::SLOT_ATTRIBUTES] = attributes_object;

    QJsonObject abilities_object;
    _abilities.write_to_json(abilities_object);
    object[json_constants::SLOT_ABILITIES] = abilities_object;
  }

  unsigned int character::id() const
  {
    return _id;
  }
}
