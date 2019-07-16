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
      _character_caste(static_cast<int>(caste)),
      _attributes(attributes),
      _abilities(abilities),
      _virtues(virtues),
      _power(power_container)
  { };


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

  attribute character::get_attribute(attribute_names::attribute name) const
  {
    return _attributes.at(name);
  }

  void character::set_attribute(attribute_names::attribute name, attribute attribute)
  {
    _attributes[name] = attribute;
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

  void character::serialisation()
  {
    synch(json_constants::SLOT_NAME , _name);
    synch(json_constants::SLOT_ID   , _id);
    synch(json_constants::SLOT_CASTE, _character_caste);
    synch(json_constants::SLOT_ATTRIBUTES, _attributes);
    synch(json_constants::SLOT_ABILITIES, _abilities);
    synch(json_constants::SLOT_VIRTUES, _virtues);
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
