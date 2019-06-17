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

  attribute character::get_attribute(attribute_names::attribute name) const
  {
    return _attributes.value(name);
  }

  void character::set_attribute(attribute_names::attribute name, attribute attribute)
  {
    _attributes.insert(name, attribute);
  }

  ability character::get_ability(ability_names::ability name, const QString& ability_declination) const
  {
    return _abilities.value(name).get_ability(ability_declination);
  }

  ability_group character::get_ability_group(ability_names::ability name) const
  {
    return _abilities.value(name);
  }

  void character::set_ability(ability_names::ability name, ability_group ability)
  {
    _abilities.insert(name, ability);
  }

  void character::read_from_json(const QJsonObject &object)
  {
    _name = object[json_constants::SLOT_NAME].toString();
    _id = static_cast<unsigned int>(object[json_constants::SLOT_ID].toInt());
    _character_caste = static_cast<exalt::caste>(object[json_constants::SLOT_CASTE].toInt());

    _attributes.read_from_json(object[json_constants::SLOT_ATTRIBUTES].toObject());
    _abilities.read_from_json(object[json_constants::SLOT_ABILITIES].toObject());
    _virtues.read_from_json(object[json_constants::SLOT_VIRTUES].toObject());
  }

  void character::write_to_json(QJsonObject &object) const
  {
    object[json_constants::SLOT_NAME] = _name;
    object[json_constants::SLOT_ID] = QString::number(_id);
    object[json_constants::SLOT_CASTE] = static_cast<int>(_character_caste);

    QJsonObject attributes_object;
    _attributes.write_to_json(attributes_object);
    object[json_constants::SLOT_ATTRIBUTES] = attributes_object;

    QJsonObject abilities_object;
    _abilities.write_to_json(abilities_object);
    object[json_constants::SLOT_ABILITIES] = abilities_object;

    QJsonObject virtues_object;
    _virtues.write_to_json(virtues_object);
    object[json_constants::SLOT_VIRTUES] = virtues_object;
  }

  unsigned int character::id() const
  {
    return _id;
  }

  exalt::caste character::caste() const
  {
    return _character_caste;
  }
}
