#pragma once

#include "character.h"

namespace calculator {
  namespace worker {
    class abstract_calculator_worker
    {
    public:
      virtual long int compute_dodge_dv(const character::character& c) const = 0;
      virtual long int compute_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const = 0;
      virtual long int compute_heavy_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const = 0;
      virtual long int compute_mental_dodge_dv(const character::character& c) const = 0;
      virtual long int compute_mental_parry_dv(const character::character& c, character::attribute_names::attribute parry_attribute) const = 0;
      virtual long int compute_persona(const character::character& c) const = 0;

      virtual ~abstract_calculator_worker() {}
    };
  }
}

