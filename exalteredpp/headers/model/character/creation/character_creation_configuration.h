#pragma once

#include <list>
#include <map>
#include "creation/character_type_model.h"
#include "attributes/attribute_names.h"
#include "abilities/ability.h"
#include "abilities/ability_group.h"

namespace character {
  namespace creation {

    struct character_creation_configuration
    {
    public:
      character_type type;
      std::list<attribute::attribute_enum> primary_attributes, secondary_attributes, tertiary_attributes;
      std::list<ability::ability_enum> caste_abilities, favorite_abilities;

      std::map<ability::ability_enum, ability::ability_group> ability_values;
      std::map<attribute::attribute_enum, unsigned int> attribute_values;

      bool is_valid() const;
      std::list<std::string> errors;

    };
  }
}
