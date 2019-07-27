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

    long int compute_dodge_dv(const character::character& c) const override;
    long int compute_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const override;
    long int compute_heavy_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const override;
    long int compute_mental_dodge_dv(const character::character& c) const override;
    long int compute_mental_parry_dv(const character::character& c, character::attribute_names::attribute parry_attribute) const override;
    long int compute_persona(const character::character& c) const override;

    virtual ~derived_value_calculator() override;
  private:
    worker_map calculator_workers;
  };

}
