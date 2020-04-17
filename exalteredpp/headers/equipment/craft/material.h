#ifndef MATERIAL_H
#define MATERIAL_H

#include "../thirdparty/serialisable/serialisable.hpp"

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

    class material : public Serialisable
    {
    public:
      material();

      material_category category() const;
      void set_category(const material_category &category);

      submaterial_category subcategory() const;
      void set_subcategory(const submaterial_category &subcategory);

      hardness hardness() const;
      void set_hardness(const enum hardness &hardness);

      std::string name() const;
      void set_name(const std::string &name);

      unsigned short craft_resistance() const;
      void set_craft_resistance(unsigned short craft_resistance);

      unsigned short cost() const;
      void set_cost(unsigned short cost);

      unsigned short availability() const;
      void set_availability(unsigned short availability);

      unsigned short tenaciousness() const;
      void set_tenaciousness(unsigned short tenaciousness);

      unsigned short break_point() const;
      void set_break_point(unsigned short break_point);

      unsigned short slots_taken() const;
      void set_slots_taken(unsigned short slots_taken);

      unsigned short minimum() const;
      void set_minimum(unsigned short minimum);

      void with_soak(combat::damage_type_enum damage, short int soak);
      short int soak(combat::damage_type_enum damage) const;

      void with_damage_bonus(combat::damage_type_enum damage, short int d_bonus);
      short int damage_bonus(combat::damage_type_enum damage) const;

      bool changes_damage_type() const;
      void set_changes_damage_type(bool changes_damage_type);

      combat::damage_type_enum overridden_damage_type() const;
      void set_overridden_damage_type(const combat::damage_type_enum &overridden_damage_type);

      short defense_bonus() const;
      void set_defense_bonus(short defense_bonus);

      short precision_bonus() const;
      void set_precision_bonus(short precision_bonus);

      short drill_bonus() const;
      void set_drill_bonus(short drill_bonus);

      short im_bonus() const;
      void set_im_bonus(short im_bonus);

      void serialisation() override;

    private:
      material_category _category;
      submaterial_category _subcategory;
      enum hardness _hardness;
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
