#pragma once

#include <string>
#include "../thirdparty/serialisable/serialisable.hpp"
#include <social/persona.h>
#include "attributes/attributes.h"
#include "abilities/abilities.h"
#include "abilities/ability_names.h"
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
                const attribute::attributes attribute,
                const ability::abilities abilities,
                const virtues::virtues virtues,
                const power::power_container power_container,
                const unsigned int id = 0);


      character(const std::string& serialised_data);

      // character fields
      std::string name() const;
      void set_name(const std::string& new_name);

      creation::character_type type() const;
      void set_type(creation::character_type type);

      attribute::attributes attributes() const;
      int attribute(attribute::attribute_enum name) const;
      void set_attribute(attribute::attribute_enum name, int value);

      ability::ability_group get_ability_group(ability::ability_enum name) const;
      ability::ability get_ability(ability::ability_enum name, const std::string& ability_declination = ability::ability_declination::NO_DECLINATION) const;
      ability::ability get_ability(const ability::detailed_ability& detailed_ability) const;
      bool has_ability(const ability::detailed_ability& detailed_ability) const;
      void set_ability(ability::ability_enum name, ability::ability_group ability);
      void set_ability_value(ability::ability_enum name, int new_val);
      void set_ability_value(ability::detailed_ability name, int new_val);
      void add_ability_specialisation(ability::ability_enum name, ability::specialisation specialisation);

      virtues::virtue virtue(virtues::virtue_enum v) const;
      virtues::virtue& virtue(virtues::virtue_enum v);
      unsigned int vice_value() const;
      virtues::vice_enum vice() const;
      void set_vice(virtues::vice_enum v, unsigned int vice_value);

      power::willpower& willpower();
      power::willpower willpower() const;
      power::essence& essence();
      power::essence essence() const;
      power::logos& logos();
      power::logos  logos() const;
      power::health& health();
      power::health  health() const;

      narrative::experience_cluster& experience();
      narrative::experience_cluster experience() const;

      unsigned int id() const;
      exalt::caste caste() const;

      virtual void serialisation() override;
      virtual ~character();

    private:
      std::string               _name;
      creation::character_type  _type;
      unsigned int              _id;

      exalt::caste                  _character_caste;
      attribute::attributes         _attributes;
      ability::abilities            _abilities;
      virtues::virtues              _virtues;
      power::power_container        _power;
      social::persona               _persona;
      narrative::experience_cluster _experience;

    };
}
