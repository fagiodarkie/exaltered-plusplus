#include "equipment/craft/weapon_project.h"

#include "serialisation/json_constants.h"

namespace equipment {
  namespace craft {

    attack_stat::attack_stat()
      : _im(0), _precision(0), _damage(0), _range(0), _cadence(0),_minimum_damage(0), _drill(0),
        _damage_type(damage_type_enum::BASHING),
        _precision_attribute(attribute::attribute_enum::DEXTERITY), _damage_attribute(attribute::attribute_enum::STRENGTH) { }

    attack_stat::attack_stat(int im, int precision, int damage, int range, int cadence, int min_damage, int drill,
                damage_type_enum damage_type,
                attribute::attribute_enum precision_attribute, attribute::attribute_enum damage_attribute)
      : _im(im), _precision(precision), _damage(damage), _range(range), _cadence(cadence),_minimum_damage(min_damage), _drill(drill),
        _damage_type(damage_type),
        _precision_attribute(precision_attribute), _damage_attribute(damage_attribute) { }

    attack_stat::attack_stat(const attack_stat& o)
      : _im(o._im), _precision(o._precision), _damage(o._damage), _range(o._range), _cadence(o._cadence),
        _minimum_damage(o._minimum_damage), _drill(o._drill), _damage_type(o._damage_type),
        _precision_attribute(o._precision_attribute), _damage_attribute(o._damage_attribute), _notes(o._notes) { }

    void attack_stat::serialisation()
    {
      synch(serialisation::json_constants::SLOT_CRAFT_IM_BONUS, _im);
      synch(serialisation::json_constants::SLOT_CRAFT_PRECISION_BONUS, _precision);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_DAMAGE_BONUS, _damage);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_RANGE, _range);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_CADENCE, _cadence);
      synch(serialisation::json_constants::SLOT_CRAFT_MIN_DAMAGE, _minimum_damage);
      synch(serialisation::json_constants::SLOT_CRAFT_DRILL_BONUS, _drill);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_DAMAGE_TYPE, _damage_type);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_PRECISION_ATTRIBUTE, _precision_attribute);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_DAMAGE_ATTRIBUTE, _damage_attribute);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_NOTES, _notes);
    }

    const attack_stat attack_stat::IMPROVISED_BASH(8, -3, 0, 1, 2, 0, 0, damage_type_enum::BASHING, attribute::attribute_enum::DEXTERITY, attribute::attribute_enum::STRENGTH);
    const attack_stat attack_stat::IMPROVISED_SLASH(5, -3, 0, 1, 3, 0, 0, damage_type_enum::LETHAL, attribute::attribute_enum::DEXTERITY, attribute::attribute_enum::STRENGTH);
    const attack_stat attack_stat::IMPROVISED_THROW(5, -3, 0, 1, 2, 0, 0, damage_type_enum::BASHING, attribute::attribute_enum::DEXTERITY, attribute::attribute_enum::STRENGTH);
    const attack_stat attack_stat::IMPROVISED_GRAPPLE(5, -3, -10, 1, 1, 0, 0, damage_type_enum::BASHING, attribute::attribute_enum::DEXTERITY, attribute::attribute_enum::STRENGTH);

    weapon_project::weapon_project()
      : _defense(0), _default_attack(attack_type::BASH) { }

    weapon_project::weapon_project(const weapon_project& o)
      : _project_name(o._project_name), _defense(o._defense), _slots(o._slots), _default_attack(o._default_attack),
        _stats(o._stats), _attributes(o._attributes), _minimums(o._minimums), _possible_abilities(o._possible_abilities), _weapon_notes(o._weapon_notes) { }

    std::string weapon_project::name() const
    {
      return _project_name;
    }

    int weapon_project::precision_bonus(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._precision;
    }
    int weapon_project::base_damage(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._damage;
    }
    int weapon_project::defense() const
    {
      return _defense;
    }
    int weapon_project::IM(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._im;
    }
    int weapon_project::minimum_damage(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._minimum_damage;
    }
    int weapon_project::drill(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._drill;
    }
    float weapon_project::range(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._range;
    }
    damage_type_enum weapon_project::damage_type(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._damage_type;
    }
    bool weapon_project::can_be_used_with(ability::ability_name ability) const
    {
      return commons::contains(_possible_abilities, ability);
    }
    bool weapon_project::is(attack_attribute attribute) const
    {
      return commons::contains(_attributes, attribute);
    }
    bool weapon_project::requires_minimum_for(attribute::attribute_enum attribute) const
    {
      return _minimums.find((int)attribute) != _minimums.end();
    }
    unsigned short int weapon_project::minimum_for(attribute::attribute_enum attribute) const
    {
      return requires_minimum_for(attribute) ? _minimums.at((int)attribute) : 0;
    }
    attribute::attribute_enum weapon_project::precision_attribute(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._precision_attribute;
    }
    attribute::attribute_enum weapon_project::damage_attribute(attack_type a_type) const
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      return _stats.at((int)a_type)._damage_attribute;
    }
    std::vector<ability::ability_name> weapon_project::relevant_abilities() const
    {
      return _possible_abilities;
    }
    unsigned short weapon_project::total_slots() const
    {
      return _slots;
    }

    weapon_project& weapon_project::with_stat(const attack_stat& stat, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type] = stat;
      return *this;
    }

    weapon_project& weapon_project::with_precision(int precision, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._precision = precision;
      return *this;
    }

    weapon_project& weapon_project::with_defense(int defense)
    {
      _defense = defense;
      return *this;
    }

    weapon_project& weapon_project::with_im(int im, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._im = im;
      return *this;
    }

    weapon_project& weapon_project::with_base_damage(int base_damage, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._damage = base_damage;
      return *this;
    }

    weapon_project& weapon_project::with_damage_type(damage_type_enum damage_type, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._damage_type = damage_type;
      return *this;
    }

    weapon_project& weapon_project::with_drill(unsigned short int drill, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._drill = drill;
      return *this;
    }

    weapon_project& weapon_project::with_min_damage(unsigned short int min, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._minimum_damage = min;
      return *this;
    }

    weapon_project& weapon_project::with_range(float range, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._range = range;
      return *this;
    }

    weapon_project& weapon_project::requires_attribute(attribute::attribute_enum attribute, unsigned short int minimum)
    {
      _minimums[(int)attribute] = minimum;
      return *this;
    }

    weapon_project& weapon_project::does_not_require(attribute::attribute_enum attribute)
    {
      _minimums.erase((int)attribute);
      return *this;
    }

    weapon_project& weapon_project::usually_attacks_with(attack_type default_attack)
    {
      _default_attack = default_attack;
      return *this;
    }

    weapon_project& weapon_project::with(attack_attribute attribute)
    {
      if (!is(attribute))
        _attributes.push_back(attribute);
      return *this;
    }

    weapon_project& weapon_project::without(attack_attribute attribute)
    {
      if (is(attribute))
        _attributes.erase(find(_attributes.begin(), _attributes.end(), attribute));
      return *this;
    }

    weapon_project& weapon_project::use_with(ability::ability_name ability)
    {
      if (!can_be_used_with(ability))
        _possible_abilities.push_back(ability);
      return *this;
    }

    weapon_project& weapon_project::do_not_use_with(ability::ability_name ability)
    {
      if (can_be_used_with(ability))
        _possible_abilities.erase(find(_possible_abilities.begin(), _possible_abilities.end(), ability));
      return *this;
    }

    weapon_project& weapon_project::with_name(const std::string& name)
    {
      _project_name = name;
      return *this;
    }

    weapon_project& weapon_project::requires_for_precision(attribute::attribute_enum precision_attribute, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._precision_attribute = precision_attribute;
      return *this;
    }

    weapon_project& weapon_project::uses_for_damage(attribute::attribute_enum damage_attribute, attack_type a_type)
    {
      if (a_type == attack_type::DEFAULT)
        a_type = _default_attack;

      _stats[(int)a_type]._damage_attribute = damage_attribute;
      return *this;
    }

    weapon_project& weapon_project::with_slots(unsigned short slot_number)
    {
      _slots = slot_number;
      return *this;
    }

    void weapon_project::serialisation()
    {
      synch(serialisation::json_constants::SLOT_NAME,                         _project_name);
      synch(serialisation::json_constants::SLOT_CRAFT_DEFENSE_BONUS,          _defense);
      synch(serialisation::json_constants::SLOT_CRAFT_SLOTS,                  _slots);
      synch(serialisation::json_constants::SLOT_CRAFT_DEFAULT_ATTACK,         _default_attack);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_GENERIC,          _stats);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_ATTRIBUTES,       _attributes);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_MINIMUMS,         _minimums);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_ABILITIES,        _possible_abilities);
      synch(serialisation::json_constants::SLOT_CRAFT_STATS_NOTES,            _weapon_notes);
    }

  }
}
