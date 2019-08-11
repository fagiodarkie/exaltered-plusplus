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

    void calculate_with(character::creation::character_type character_type, std::shared_ptr<worker::abstract_calculator_worker> worker);

    long int compute_dodge_dv                 (const character::character& c) const override;
    long int compute_parry_dv                 (const character::character& c, character::ability_names::ability_enum parry_ability) const override;
    long int compute_heavy_parry_dv           (const character::character& c, character::ability_names::ability_enum parry_ability) const override;
    long int compute_mental_dodge_dv          (const character::character& c) const override;
    long int compute_mental_parry_dv          (const character::character& c, character::attribute_names::attribute parry_attribute) const override;
    long int compute_persona                  (const character::character& c) const override;
    long int compute_persona                  (const character::creation::character_type& type, const character::attributes& attributes, const character::power::willpower& willpower, const character::power::essence& essence) const override;
    long int compute_bashing_soak             (const character::character& c) const override;
    long int compute_lethal_soak              (const character::character& c) const override;
    long int compute_aggravated_soak          (const character::character& c) const override;
    long int compute_natural_bashing_soak     (const character::character& c) const override;
    long int compute_natural_lethal_soak      (const character::character& c) const override;
    long int compute_natural_aggravated_soak  (const character::character& c) const override;
    long int compute_personal_essence         (const character::character& c) const override;
    long int compute_peripheral_essence       (const character::character& c) const override;
    long int compute_spiritual_essence        (const character::character& c) const override;
    long int compute_celestial_portion        (const character::character& c) const override;
    long int compute_life_points              (const character::character& c) const override;
    double   starting_darkana                 (const character::creation::character_type& c) const override;
    long int starting_essence                 (const character::creation::character_type& c) const override;
    long int starting_logos                   (const character::creation::character_type& c) const override;

    virtual ~derived_value_calculator() override;
  private:
    worker_map calculator_workers;
  };

}
