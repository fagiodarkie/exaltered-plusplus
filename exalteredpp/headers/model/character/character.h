#pragma once

#include <string>
#include "../thirdparty/serialisable/serialisable.hpp"
#include <social/persona.h>
#include "character/attributes/attributes.h"
#include "character/abilities/abilities.h"
#include "creation/character_type_model.h"
#include "exalt/exalt_caste.h"
#include "virtues/virtues.h"
#include "power/power_container.h"
#include "narrative/experience_cluster.h"

namespace character
{
  class character : public Serialisable
  {
    public:
      // constructors
      character(const std::string name,
                const creation::character_type type,
                const exalt::caste caste,
                const attributes attributes,
                const abilities abilities,
                const virtues::virtues virtues,
                const power::power_container power_container,
                const unsigned int id = 0);


      character(const std::string& serialised_data);

      // character fields
      std::string get_name() const;
      void set_name(const std::string& new_name);

      creation::character_type get_type() const;
      void set_type(creation::character_type type);

      attributes get_attributes() const;
      attribute get_attribute(attribute_names::attribute name) const;
      void set_attribute(attribute_names::attribute name, attribute attribute);
      void set_attribute_value(attribute_names::attribute name, int new_val);

      ability_group get_ability_group(ability_names::ability_enum name) const;
      ability get_ability(ability_names::ability_enum name, const std::string& ability_declination = ability_names::ability_declination::NO_DECLINATION) const;
      ability get_ability(const ability_names::detailed_ability& detailed_ability) const;
      bool has_ability(const ability_names::detailed_ability& detailed_ability) const;
      void set_ability(ability_names::ability_enum name, ability_group ability);
      void set_ability_value(ability_names::ability_enum name, int new_val);
      void set_ability_value(ability_names::detailed_ability name, int new_val);

      virtues::virtue get_virtue(virtues::virtue_enum v) const;
      virtues::virtue& get_virtue(virtues::virtue_enum v);
      unsigned int get_vice_value() const;
      virtues::vice_enum get_vice() const;
      void set_vice(virtues::vice_enum v, unsigned int vice_value);

      power::willpower& get_willpower();
      power::willpower get_willpower() const;
      power::essence& get_essence();
      power::essence get_essence() const;
      power::logos& get_logos();
      power::logos  get_logos() const;
      power::health& get_health();
      power::health  get_health() const;

      narrative::experience_cluster& get_experience();
      narrative::experience_cluster get_experience() const;

      unsigned int id() const;
      exalt::caste caste() const;

      virtual void serialisation() override;
      virtual ~character();

    private:
      std::string               _name;
      creation::character_type  _type;
      unsigned int              _id;

      exalt::caste                  _character_caste;
      attributes                    _attributes;
      abilities                     _abilities;
      virtues::virtues              _virtues;
      power::power_container        _power;
      social::persona               _persona;
      narrative::experience_cluster _experience;

    };
}
