#pragma once

#include "character.h"

namespace calculator {
  namespace worker {
    class abstract_calculator_worker
    {
    public:
      // VD & soak
      virtual long int compute_dodge_dv                 (const character::character& c) const = 0;
      virtual long int compute_parry_dv                 (const character::character& c, character::ability_names::ability_enum parry_ability) const = 0;
      virtual long int compute_heavy_parry_dv           (const character::character& c, character::ability_names::ability_enum parry_ability) const = 0;

      virtual long int compute_bashing_soak             (const character::character& c) const = 0;
      virtual long int compute_lethal_soak              (const character::character& c) const = 0;
      virtual long int compute_aggravated_soak          (const character::character& c) const = 0;
      virtual long int compute_natural_bashing_soak     (const character::character& c) const = 0;
      virtual long int compute_natural_lethal_soak      (const character::character& c) const = 0;
      virtual long int compute_natural_aggravated_soak  (const character::character& c) const = 0;

      virtual long int compute_hindrance                (const character::character& c) const  = 0;
      virtual long int compute_stance_bonus             (const character::character& c) const  = 0;
      virtual long int compute_parry_balance            (const character::character& c) const  = 0;
      virtual long int compute_dodge_balance            (const character::character& c) const  = 0;

      virtual long int compute_mental_dodge_dv          (const character::character& c) const = 0;
      virtual long int compute_mental_parry_dv          (const character::character& c, character::attribute_names::attribute parry_attribute) const = 0;
      virtual long int compute_persona                  (const character::character& c) const = 0;
      virtual long int compute_persona                  (const character::creation::character_type& type, const character::attributes& attributes, const character::power::willpower& willpower, const character::power::essence& essence) const = 0;
      virtual long int compute_resilience               (const character::character& c) const  = 0;

      // Essence & Logos
      virtual long int compute_personal_essence         (const character::character& c) const = 0;
      virtual long int compute_peripheral_essence       (const character::character& c) const = 0;
      virtual long int compute_spiritual_essence        (const character::character& c) const = 0;
      virtual long int compute_celestial_portion        (const character::character& c) const = 0;
      virtual unsigned int compute_life_points          (const character::character& c) const = 0;

      // starting values
      virtual double starting_darkana                   (const character::creation::character_type& c) const = 0;
      virtual unsigned int starting_essence             (const character::creation::character_type& c) const = 0;
      virtual unsigned int starting_logos               (const character::creation::character_type& c) const = 0;
      virtual unsigned int starting_willpower           (const character::character& c) const = 0;

      virtual ~abstract_calculator_worker() {}
    };
  }
}

