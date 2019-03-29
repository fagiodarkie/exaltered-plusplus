#include "character/character.h"
#include "json_constants.h"

using serialisation::json_constants;

namespace character
{
  character::character(QString name) : _name(name)
  {
    for (attribute_name att_name : ATTRIBUTE_NAME.keys())
      {
        attribute attribute(ATTRIBUTE_NAME.value(att_name), (qrand() % 5) + 1);
        set_attribute(att_name, attribute);
      }
  };

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

  attribute character::get_attribute(attribute_name name) const
  {
    return _attributes.value(name);
  }

  void character::set_attribute(attribute_name name, attribute attribute)
  {
    _attributes.insert(name, attribute);
  }

  ability character::get_ability(ability_name name, const QString& ability_declination) const
  {
    return _abilities.value(name).get_ability(ability_declination);
  }

  ability_group character::get_ability_group(ability_name name) const
  {
    return _abilities.value(name);
  }

  void character::set_ability(ability_name name, ability_group ability)
  {
    _abilities.insert(name, ability);
  }

  void character::read_from_json(const QJsonObject &object)
  {
    _name = object[json_constants::SLOT_NAME].toString();
    _attributes.read_from_json(object[json_constants::SLOT_ATTRIBUTES].toObject());
    _abilities.read_from_json(object[json_constants::SLOT_ABILITIES].toObject());
  }

  void character::write_to_json(QJsonObject &object) const
  {
    object[json_constants::SLOT_NAME] = _name;

    QJsonObject attributes_object;
    _attributes.write_to_json(attributes_object);
    object[json_constants::SLOT_ATTRIBUTES] = attributes_object;

    QJsonObject abilities_object;
    _abilities.write_to_json(abilities_object);
    object[json_constants::SLOT_ABILITIES] = abilities_object;
  }
}
