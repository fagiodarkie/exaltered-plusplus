#include "calculator/derived_value_calculator.h"

namespace calculator {

  derived_value_calculator::derived_value_calculator(worker_map workers) : calculator_workers(workers) { }

  void derived_value_calculator::calculate_with(character::creation::character_type character_type, std::shared_ptr<worker::abstract_calculator_worker> worker)
  {
    calculator_workers[character_type] = worker;
  }

  long int derived_value_calculator::compute_dodge_dv(const character::character& c) const
  {
    return calculator_workers.at(c.get_type())->compute_dodge_dv(c);
  }

  long int derived_value_calculator::compute_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const
  {
    return calculator_workers.at(c.get_type())->compute_parry_dv(c, parry_ability);
  }

  long int derived_value_calculator::compute_heavy_parry_dv(const character::character& c, character::ability_names::ability_enum parry_ability) const
  {
    return calculator_workers.at(c.get_type())->compute_heavy_parry_dv(c, parry_ability);
  }

  long int derived_value_calculator::compute_mental_dodge_dv(const character::character& c) const
  {
    return calculator_workers.at(c.get_type())->compute_mental_dodge_dv(c);
  }

  long int derived_value_calculator::compute_mental_parry_dv(const character::character& c, character::attribute_names::attribute parry_attribute) const
  {
    return calculator_workers.at(c.get_type())->compute_mental_parry_dv(c, parry_attribute);
  }

  long int derived_value_calculator::compute_persona(const character::character& c) const
  {
    return calculator_workers.at(c.get_type())->compute_persona(c);
  }


}
