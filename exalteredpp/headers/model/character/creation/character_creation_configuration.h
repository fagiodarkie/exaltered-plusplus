#pragma once

#include <list>
#include <map>
#include "creation/character_type_model.h"
#include "attributes/attributes.h"
#include "abilities/abilities.h"

namespace character {
  namespace creation {

    struct character_creation_configuration
    {
    public:
      character_type type;
      std::list<attribute::attribute_enum> primary_attributes, secondary_attributes, tertiary_attributes;
      std::list<ability::ability_enum> caste_abilities, favorite_abilities;

      ability::abilities abilities;
      attribute::attributes attributes;

    };
  }
}
