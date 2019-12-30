#include "character/character.h"
#include "json_constants.h"

using serialisation::json_constants;

namespace character
{
  character::character(const std::string name,
                       const creation::character_type type,
                       const exalt::caste caste,
                       const attributes attributes,
                       const abilities abilities,
                       const virtues::virtues virtues,
                       const power::power_container power_container,
                       const unsigned int id)
    : _name(name),
      _type(type),
      _id(id),
      _character_caste(caste),
      _attributes(attributes),
      _abilities(abilities),
      _virtues(virtues),
      _power(power_container)
  { };

  character::character(const std::string& serialised_data)
  {
    deserialise(serialised_data);
  }

  std::string character::get_name() const
  {
    return _name;
  }

  void character::set_name(const std::string& new_name)
  {
    _name = new_name;
  }

  creation::character_type character::get_type() const
  {
    return _type;
  }

  void character::set_type(creation::character_type type)
  {
    _type = type;
  }

  attributes character::get_attributes() const
  {
    return _attributes;
  }

  attribute character::get_attribute(attribute_names::attribute name) const
  {
    return _attributes.at(name);
  }

  void character::set_attribute(attribute_names::attribute name, attribute attribute)
  {
    _attributes[name] = attribute;
  }

  void character::set_attribute_value(attribute_names::attribute name, int new_val)
  {
    _attributes[name].set_value(new_val);
  }

  ability character::get_ability(ability_names::ability_enum name, const std::string& ability_declination) const
  {
    return _abilities.at(name).get_ability(ability_declination);
  }

  ability_group character::get_ability_group(ability_names::ability_enum name) const
  {
    return _abilities.at(name);
  }

  void character::set_ability(ability_names::ability_enum name, ability_group ability)
  {
    _abilities[name] = ability;
  }

  void character::set_ability_value(ability_names::ability_enum name, int new_val)
  {
    _abilities[name].set_ability_value(ability_names::ability_declination::NO_DECLINATION, new_val);
  }

  void character::set_ability_value(ability_names::detailed_ability name, int new_val)
  {
    _abilities[name.ability].set_ability_value(name.declination, new_val);
  }

  power::willpower& character::get_willpower()
  {
    return _power.get_willpower();
  }

  power::willpower character::get_willpower() const
  {
    return _power.get_willpower();
  }

  power::essence& character::get_essence()
  {
    return _power.get_essence();
  }

  power::essence character::get_essence() const
  {
    return _power.get_essence();
  }

  power::logos& character::get_logos()
  {
    return _power.get_logos();
  }
  power::logos  character::get_logos() const
  {
    return _power.get_logos();
  }

  power::health& character::get_health()
  {
    return _power.get_health();
  }
  power::health  character::get_health() const
  {
    return _power.get_health();
  }

  virtues::virtue   character::get_virtue(virtues::virtue_enum v) const
  {
    return _virtues.at(v);
  }
  virtues::virtue&  character::get_virtue(virtues::virtue_enum v)
  {
    return _virtues[v];
  }
  unsigned int      character::get_vice_value() const
  {
    return _virtues.vice_value();
  }
  virtues::vice_enum character::get_vice() const
  {
    return _virtues.vice();
  }
  void              character::set_vice(virtues::vice_enum v, unsigned int vice_value)
  {
    _virtues.set_vice_type(v);
    _virtues.set_vice_value(vice_value);
  }

  narrative::experience_cluster character::get_experience() const
  {
    return _experience;
  }

  narrative::experience_cluster& character::get_experience()
  {
    return _experience;
  }

  void character::serialisation()
  {
    synch(json_constants::SLOT_NAME , _name);
    synch(json_constants::SLOT_ID   , _id);
    synch(json_constants::SLOT_CHARACTER_TYPE, _type);
    synch(json_constants::SLOT_CASTE, _character_caste);
    synch(json_constants::SLOT_ATTRIBUTES, _attributes);
    synch(json_constants::SLOT_ABILITIES, _abilities);
    synch(json_constants::SLOT_VIRTUES, _virtues);
    synch(json_constants::SLOT_POWER,   _power);
    synch(json_constants::SLOT_PERSONA, _persona);
    synch(json_constants::SLOT_EXPERIENCE, _persona);
  }

  unsigned int character::id() const
  {
    return _id;
  }

  exalt::caste character::caste() const
  {
    return _character_caste;
  }

  character::~character() {}
}
