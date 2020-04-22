#ifndef WEAPON_PROJECT_H
#define WEAPON_PROJECT_H

#include "../thirdparty/serialisable/serialisable.hpp"
#include "combat/attack_defines.h"
#include "attributes/attribute_names.h"
#include "abilities/ability_names.h"
#include "abilities/specialisation.h"
#include "common/serialisable_map.h"
#include "craft_defines.h"
#include "material.h"

namespace equipment {
  namespace craft {

    using combat::damage_type_enum;
    using combat::attack_attribute;

    class attack_stat : public Serialisable
    {
    public:

      attack_stat();
      attack_stat(int im, int precision, int damage, int range, int cadence, int min_damage, int drill,
                  damage_type_enum damage_type,
                  attribute::attribute_enum precision_attribute, attribute::attribute_enum damage_attribute);

      static const attack_stat IMPROVISED_BASH, IMPROVISED_SLASH, IMPROVISED_THROW, IMPROVISED_GRAPPLE;

      int _im, _precision, _damage, _range, _cadence, _minimum_damage, _drill;
      damage_type_enum _damage_type;
      attribute::attribute_enum _precision_attribute, _damage_attribute;
      std::vector<note> _notes;

      void serialisation() override;
    };

    class weapon_project : public Serialisable
    {
    public:

      static const unsigned short STANDARD_WEAPON_SLOTS = 3, HEAVY_WEAPON_SLOTS = 4;

      weapon_project();

      std::string name() const;
      int precision_bonus(attack_type = attack_type::DEFAULT) const;
      int base_damage(attack_type = attack_type::DEFAULT) const;
      int defense() const;
      int IM(attack_type = attack_type::DEFAULT) const;
      int minimum_damage(attack_type = attack_type::DEFAULT) const;
      int drill(attack_type = attack_type::DEFAULT) const;
      float range(attack_type = attack_type::DEFAULT) const;
      damage_type_enum damage_type(attack_type = attack_type::DEFAULT) const;
      bool can_be_used_with(ability::ability_name ability) const;
      bool is(attack_attribute attribute) const;
      bool requires_minimum_for(attribute::attribute_enum attribute) const;
      unsigned short int minimum_for(attribute::attribute_enum attribute) const;
      attribute::attribute_enum precision_attribute(attack_type = attack_type::DEFAULT) const;
      attribute::attribute_enum damage_attribute(attack_type = attack_type::DEFAULT) const;
      std::vector<ability::ability_name> relevant_abilities() const;
      unsigned short int total_slots() const;

      weapon_project& with_precision(int precision, attack_type = attack_type::DEFAULT);
      weapon_project& with_defense(int defense);
      weapon_project& with_im(int im, attack_type = attack_type::DEFAULT);
      weapon_project& with_base_damage(int base_damage, attack_type = attack_type::DEFAULT);
      weapon_project& with_damage_type(damage_type_enum damage_type, attack_type = attack_type::DEFAULT);
      weapon_project& with_drill(unsigned short int drill, attack_type = attack_type::DEFAULT);
      weapon_project& with_min_damage(unsigned short int min, attack_type = attack_type::DEFAULT);
      weapon_project& with_range(float range, attack_type = attack_type::DEFAULT);
      weapon_project& requires_attribute(attribute::attribute_enum attribute,unsigned short int minimum = 1);
      weapon_project& does_not_require(attribute::attribute_enum attribute);
      weapon_project& usually_attacks_with(attack_type default_attack = attack_type::DEFAULT);
      weapon_project& with(attack_attribute attribute);
      weapon_project& without(attack_attribute attribute);
      weapon_project& use_with(ability::ability_name ability);
      weapon_project& do_not_use_with(ability::ability_name ability);
      weapon_project& with_name(const std::string& name);
      weapon_project& requires_for_precision(attribute::attribute_enum precision_attribute, attack_type = attack_type::DEFAULT);
      weapon_project& uses_for_damage(attribute::attribute_enum damage_attribute, attack_type = attack_type::DEFAULT);
      weapon_project& with_slots(unsigned short int slot_number);

      void serialisation() override;

    private:

      std::string _project_name;
      int _defense;
      unsigned short int _slots;
      attack_type _default_attack;
      serialisable_int_map<attack_stat> _stats;
      std::vector<attack_attribute> _attributes;
      serialisable_int_map<unsigned short int> _minimums;
      std::vector<ability::ability_name> _possible_abilities;
      std::vector<note> _weapon_notes;

    };
  }
}
#endif // WEAPON_PROJECT_H
