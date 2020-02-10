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
#include "power/essence.h"
#include "power/willpower.h"
#include "power/health.h"
#include "power/logos.h"

#include "narrative/experience_cluster.h"

namespace character
{
  class character : public Serialisable
  {
    public:
      // constructors
      character(const std::string& name,
                const creation::character_type type,
                const exalt::caste& caste,
                const attribute::attributes& attribute,
                const ability::abilities& abilities,
                const virtues::virtues& virtues,
                const power::essence&   essence,
                const power::willpower& willpower,
                const power::health&    health,
                const power::logos&     logos,
                const unsigned int id = 0);


      character(const std::string& serialised_data);

      // character fields
      std::string name() const;
      void set_name(const std::string& new_name);

      creation::character_type type() const;
      void set_type(creation::character_type type);

      attribute::attributes attributes() const;
      int attribute(attribute::attribute_enum name) const;
      void set(attribute::attribute_enum name, int value);
      int& operator[](attribute::attribute_enum name);

      ability::ability get(ability::ability_enum name, const std::string& ability_declination = ability::ability_declination::NO_DECLINATION) const;
      ability::ability get(const ability::ability_name& detailed_ability) const;
      ability::ability& operator[](const ability::ability_name& detailed_ability);
      ability::ability& operator[](ability::ability_enum ability_e);
      ability::ability& ability(ability::ability_enum name, const std::string& ability_declination = ability::ability_declination::NO_DECLINATION);
      bool has(const ability::ability_name& detailed_ability) const;
      void set(ability::ability_name name, unsigned int new_val);
      void add(ability::ability_name name, const ability::specialisation& specialisation);
      ability::abilities abilities() const;
      ability::abilities& abilities();
      std::vector<ability::ability> abilities(ability::ability_enum ability_type) const;

      virtues::virtue   virtue(virtues::virtue_enum v) const;
      virtues::virtue&  virtue(virtues::virtue_enum v);
      unsigned int vice_value() const;
      virtues::vice_enum vice() const;
      void set_vice(virtues::vice_enum v, unsigned int vice_value);

      power::willpower& willpower();
      power::willpower  willpower() const;
      power::essence&   essence();
      power::essence    essence() const;
      power::logos&     logos();
      power::logos      logos() const;
      power::health&    health();
      power::health     health() const;

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
      social::persona               _persona;
      narrative::experience_cluster _experience;
      power::essence                _essence;
      power::willpower              _willpower;
      power::health                 _health;
      power::logos                  _logos;

    };
}
