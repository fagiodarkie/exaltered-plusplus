#pragma once

#include "character.h"
#include "combat/attack_defines.h"

namespace calculator {
  namespace worker {

    struct physical_defenses {
      unsigned int parry_vd, tower_parry_vd, dodge_vd,
        parry_balance, dodge_balance, hindrance, stance;
    };

    struct mental_defenses {
      unsigned int mental_dodge_vd, charisma_parry_vd, manipulation_parry_vd, appearance_parry_vd,
        resilience;
    };

    struct soak_values {
      unsigned int hardness;
      std::map<combat::damage_type_enum, unsigned int> natural_soak;
      std::map<combat::body_target, std::map<combat::damage_type_enum, unsigned int>> armored_soak;
    };

    class abstract_calculator_worker
    {
    public:

      virtual physical_defenses compute_physical_vd(const character::character& c, ability::ability_name parry_ability, int weapon_defense_value) const = 0;
      virtual mental_defenses   compute_mental_vd(const character::character& c) const = 0;
      virtual soak_values       compute_soak_values(const character::character& c) const = 0;

      // Essence & Logos
      virtual long int compute_personal_essence         (const character::character& c) const = 0;
      virtual long int compute_peripheral_essence       (const character::character& c) const = 0;
      virtual long int compute_spiritual_essence        (const character::character& c) const = 0;
      virtual long int compute_celestial_portion        (const character::character& c) const = 0;
      virtual unsigned int compute_life_points          (const character::character& c) const = 0;
      virtual long int compute_persona                  (const character::creation::character_type& type, const attribute::attributes& attribute, const power::willpower& willpower, const power::essence& essence) const = 0;
      virtual long int compute_persona                  (const character::character& c) const = 0;

      // starting values
      virtual unsigned int starting_khan                (const character::creation::character_type& c) const = 0;
      virtual unsigned int starting_essence             (const character::creation::character_type& c) const = 0;
      virtual unsigned int starting_logos               (const character::creation::character_type& c) const = 0;
      virtual unsigned int starting_willpower           (const character::character& c) const = 0;

      virtual ~abstract_calculator_worker() {}
    };
  }
}

