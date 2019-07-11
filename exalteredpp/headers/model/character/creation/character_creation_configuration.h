#pragma once

#include <QList>
#include "creation/character_type_model.h"
#include "attributes/attribute_names.h"
#include "abilities/ability_names.h"
#include "abilities/ability_group.h"

namespace character {
  namespace creation {

    struct character_creation_configuration
    {
    public:
      character_type type;
      QList<attribute_names::attribute> primary_attributes, secondary_attributes, tertiary_attributes;
      QList<ability_names::ability_enum> caste_abilities, favorite_abilities;

      QMap<ability_names::ability_enum, ability_group> ability_values;
      QMap<attribute_names::attribute, unsigned int> attribute_values;

      bool is_valid() const;
      QList<QString> errors;

    };
  }
}
