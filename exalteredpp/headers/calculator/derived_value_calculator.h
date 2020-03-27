#pragma once

#include <map>
#include "character.h"
#include "worker/abstract_calculator_worker.h"

namespace calculator {

  class derived_value_calculator : public worker::abstract_calculator_worker
  {
  public:
    typedef std::map<character::creation::character_type, std::shared_ptr<worker::abstract_calculator_worker>> worker_map;
    derived_value_calculator() {}
    derived_value_calculator(worker_map initial_map);

    virtual worker::physical_defenses compute_physical_vd(const character::character& c, ability::ability_name parry_ability, int weapon_defense_value = 0) const override;
    virtual worker::mental_defenses   compute_mental_vd(const character::character& c) const override;
    virtual worker::soak_values       compute_soak_values(const character::character& c) const override;
    virtual worker::mental_soak_values compute_mental_soak_values(const character::character& c) const override;

    virtual long int compute_persona                  (const character::creation::character_type& type, const attribute::attributes& attribute, const power::willpower& willpower, const power::essence& essence) const override;
    virtual long int compute_persona                  (const character::character& c) const override;

    virtual ~derived_value_calculator() override;

    long int compute_personal_essence         (const character::character& c)                const override;
    long int compute_peripheral_essence       (const character::character& c)                const override;
    long int compute_spiritual_essence        (const character::character& c)                const override;
    long int compute_celestial_portion        (const character::character& c)                const override;
    unsigned int compute_life_points          (const character::character& c)                const override;
    unsigned int starting_khan                (const character::creation::character_type& c) const override;
    unsigned int starting_essence             (const character::creation::character_type& c) const override;
    unsigned int starting_logos               (const character::creation::character_type& c) const override;
    unsigned int starting_willpower           (const character::character& c)                const override;


  private:
    worker_map calculator_workers;
  };

}
