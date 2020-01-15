#include "character/character.h"
#include "json_constants.h"

using serialisation::json_constants;

namespace character
{
  character::character(const std::string name,
                       const creation::character_type type,
                       const exalt::caste caste,
                       const attribute::attributes attributes,
                       const ability::abilities abilities,
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

  std::string character::name() const
  {
    return _name;
  }

  void character::set_name(const std::string& new_name)
  {
    _name = new_name;
  }

  creation::character_type character::type() const
  {
    return _type;
  }

  void character::set_type(creation::character_type type)
  {
    _type = type;
  }

  attribute::attributes character::attributes() const
  {
    return _attributes;
  }

  int character::attribute(attribute::attribute_enum name) const
  {
    return _attributes.at(name);
  }

  void character::set_attribute(attribute::attribute_enum name, int attribute)
  {
    _attributes[name] = attribute;
  }

  ability::ability character::get_ability(ability::ability_enum name, const std::string& ability_declination) const
  {
    if (_abilities.find(name) == _abilities.end() || !_abilities.at(name).has_ability(ability_declination))
      return ability::ability(ability::ABILITY_NAME.at(name));
    return _abilities.at(name).get_ability(ability_declination);
  }

  ability::ability character::get_ability(const ability::detailed_ability& detailed_ability) const
  {
    return get_ability(detailed_ability.ability, detailed_ability.declination);
  }

  bool character::has_ability(const ability::detailed_ability& detailed_ability) const
  {
    return _abilities.at(detailed_ability.ability).has_ability(detailed_ability.declination);
  }

  ability::ability_group character::get_ability_group(ability::ability_enum name) const
  {
    return _abilities.at(name);
  }

  void character::set_ability(ability::ability_enum name, ability::ability_group ability)
  {
    _abilities[name] = ability;
  }

  void character::set_ability_value(ability::ability_enum name, int new_val)
  {
    _abilities[name].set_ability_value(ability::ability_declination::NO_DECLINATION, new_val);
  }

  void character::set_ability_value(ability::detailed_ability name, int new_val)
  {
    _abilities[name.ability].set_ability_value(name.declination, new_val);
  }

  void character::add_ability_specialisation(ability::ability_enum name, ability::specialisation specialisation)
  {
    _abilities[name].add_specialisation(specialisation);
  }

  power::willpower& character::willpower()
  {
    return _power.willpower();
  }

  power::willpower character::willpower() const
  {
    return _power.willpower();
  }

  power::essence& character::essence()
  {
    return _power.essence();
  }

  power::essence character::essence() const
  {
    return _power.essence();
  }

  power::logos& character::logos()
  {
    return _power.logos();
  }
  power::logos  character::logos() const
  {
    return _power.logos();
  }

  power::health& character::health()
  {
    return _power.health();
  }
  power::health  character::health() const
  {
    return _power.health();
  }

  virtues::virtue   character::virtue(virtues::virtue_enum v) const
  {
    return _virtues.at(v);
  }
  virtues::virtue&  character::virtue(virtues::virtue_enum v)
  {
    return _virtues[v];
  }
  unsigned int      character::vice_value() const
  {
    return _virtues.vice_value();
  }
  virtues::vice_enum character::vice() const
  {
    return _virtues.vice();
  }
  void              character::set_vice(virtues::vice_enum v, unsigned int vice_value)
  {
    _virtues.set_vice_type(v);
    _virtues.set_vice_value(vice_value);
  }

  narrative::experience_cluster character::experience() const
  {
    return _experience;
  }

  narrative::experience_cluster& character::experience()
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
    synch(json_constants::SLOT_EXPERIENCE, _experience);
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
