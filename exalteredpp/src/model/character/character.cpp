#include "character/character.h"
#include "json_constants.h"

using serialisation::json_constants;

namespace character
{
  character::character(const std::string& name,
                       const creation::character_type type,
                       const exalt::caste& caste,
                       const attribute::attributes& attributes,
                       const ability::abilities& abilities,
                       const virtues::virtues& virtues,
                       const power::essence&   essence,
                       const power::willpower& willpower,
                       const power::health&    health,
                       const power::logos&     logos,
                       const unsigned int id)
    : _name(name),
      _type(type),
      _id(id),
      _character_caste(caste),
      _attributes(attributes),
      _abilities(abilities),
      _virtues(virtues),
      _essence(essence),
      _willpower(willpower),
      _health(health),
      _logos(logos)
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

  void character::set(attribute::attribute_enum name, int attribute)
  {
    _attributes[name] = attribute;
  }

  int& character::operator[](attribute::attribute_enum name)
  {
    return _attributes[name];
  }

  ability::ability character::get(ability::ability_enum name, const std::string& ability_declination) const
  {
    return _abilities.get(ability::ability_name(name, ability_declination));
  }

  ability::ability& character::ability(ability::ability_enum name, const std::string &ability_declination)
  {
    return _abilities[ability::ability_name(name, ability_declination)];
  }

  ability::ability character::get(const ability::ability_name& detailed_ability) const
  {
    return _abilities.get(detailed_ability);
  }

  bool character::has(const ability::ability_name& detailed_ability) const
  {
    return _abilities.has(detailed_ability);
  }

  void character::set(ability::ability_name name, unsigned int new_val)
  {
    _abilities[name] = new_val;
  }

  void character::add(ability::ability_name name, const ability::specialisation& specialisation)
  {
    _abilities[name].add(specialisation.name(), specialisation.value());
  }

  ability::ability& character::operator[](const ability::ability_name &detailed_ability)
  {
    return _abilities[detailed_ability];
  }

  ability::ability& character::operator[](ability::ability_enum detailed_ability)
  {
    return _abilities[ability::ability_name(detailed_ability)];
  }

  ability::abilities character::abilities() const
  {
    return _abilities;
  }
  ability::abilities& character::abilities()
  {
    return _abilities;
  }

  ability::abilities character::abilities(ability::ability_enum ability_type) const
  {
    return _abilities.with_type(ability_type);
  }

  power::willpower& character::willpower()
  {
    return _willpower;
  }

  power::willpower character::willpower() const
  {
    return _willpower;
  }

  power::essence& character::essence()
  {
    return _essence;
  }

  power::essence character::essence() const
  {
    return _essence;
  }

  power::logos& character::logos()
  {
    return _logos;
  }
  power::logos  character::logos() const
  {
    return _logos;
  }

  power::health& character::health()
  {
    return _health;
  }
  power::health  character::health() const
  {
    return _health;
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

  unsigned int character::stress() const
  {
    return _stress_value;
  }

  void character::increase_stress()
  {
    ++_stress_value;
  }

  void character::rest(unsigned int restored_willpower)
  {
    _willpower.restore(restored_willpower);
    _stress_value = 0;
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
    synch(json_constants::SLOT_PERSONA, _persona);
    synch(json_constants::SLOT_EXPERIENCE, _experience);
    synch(json_constants::SLOT_HEALTH   , _health   );
    synch(json_constants::SLOT_WILLPOWER, _willpower);
    synch(json_constants::SLOT_ESSENCE  , _essence  );
    synch(json_constants::SLOT_LOGOS    , _logos    );
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
