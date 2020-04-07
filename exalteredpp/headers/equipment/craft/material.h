#ifndef MATERIAL_H
#define MATERIAL_H

#include "combat/attack_defines.h"
#include <string>
#include <map>

namespace equipment {
  namespace craft {

    enum class material_category
    {
      METAL,
      WOOD,
      NON_METAL,
      FIBER,
      LUXURY_MATERIAL,
      WIRE
    };

    enum class submaterial_category
    {
      COMMON_METAL,
      UNCOMMON_METAL,
      MAGICAL_METAL,
      MAGICAL_NON_METAL,
      UNCOMMON_COMPLEX,
      VEGETAL_FIBER,
      ANIMAL_FIBER,
      CURED_ANIMAL_FIBER,
      FINE_HARD_WOOD,
      STRONG_HARD_WOOD,
      SOFT_WOOD,
      MAGICAL_FIBER
    };

    enum class hardness
    {
      SOFT,
      MEDIUM,
      HARD
    };

    class material
    {
    public:
      material();

    private:
      material_category _category;
      submaterial_category _subcategory;
      hardness _hardness;
      std::string _name;

      unsigned short int _craft_resistance, _cost, _availability, _tenaciousness, _break_point, _slots_taken, _minimum;

      short int _defense_bonus, _precision_bonus, _drill_bonus, _im_bonus;
      std::map<combat::damage_type_enum, short int> _soak, _damage_bonus;

      bool _changes_damage_type;
      combat::damage_type_enum _overridden_damage_type;
    };
  }
}

#endif // MATERIAL_H
