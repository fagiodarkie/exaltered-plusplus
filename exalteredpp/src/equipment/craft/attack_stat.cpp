#include "equipment/craft/attack_stat.h"
#include "serialisation/json_constants.h"
#include "serialisation_utils.h"

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

      SYNCH_ENUM_VECTOR(note, serialisation::json_constants::SLOT_CRAFT_STATS_NOTES, _notes)

    }

    const attack_stat attack_stat::IMPROVISED_BASH(8, -3, 0, 1, 2, 0, 0, damage_type_enum::BASHING, attribute::attribute_enum::DEXTERITY, attribute::attribute_enum::STRENGTH);
    const attack_stat attack_stat::IMPROVISED_SLASH(5, -3, 0, 1, 3, 0, 0, damage_type_enum::LETHAL, attribute::attribute_enum::DEXTERITY, attribute::attribute_enum::STRENGTH);
    const attack_stat attack_stat::IMPROVISED_THROW(5, -3, 0, 1, 2, 0, 0, damage_type_enum::BASHING, attribute::attribute_enum::DEXTERITY, attribute::attribute_enum::STRENGTH);
    const attack_stat attack_stat::IMPROVISED_GRAPPLE(5, -3, -10, 1, 1, 0, 0, damage_type_enum::BASHING, attribute::attribute_enum::DEXTERITY, attribute::attribute_enum::STRENGTH);
  }
}
