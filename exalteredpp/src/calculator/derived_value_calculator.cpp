#include "calculator/derived_value_calculator.h"

namespace calculator {

  derived_value_calculator::derived_value_calculator(worker_map workers) : calculator_workers(workers) { }

  worker::physical_defenses derived_value_calculator::compute_physical_vd(const character::character& c, ability::ability_enum parry_ability) const
  {
    return calculator_workers.at(c.type())->compute_physical_vd(c, parry_ability);
  }

  worker::mental_defenses derived_value_calculator::compute_mental_vd(const character::character& c) const
  {
    return calculator_workers.at(c.type())->compute_mental_vd(c);
  }

  long int derived_value_calculator::compute_persona(const character::character& c) const
  {
    return calculator_workers.at(c.type())->compute_persona(c);
  }

  long int derived_value_calculator::compute_persona                  (const character::creation::character_type& type, const attribute::attributes& attributes, const power::willpower& willpower, const power::essence& essence) const
  {
    return calculator_workers.at(type)->compute_persona(type, attributes, willpower, essence);
  }

  long int derived_value_calculator::compute_personal_essence         (const character::character& c) const
  {
    return calculator_workers.at(c.type())->compute_personal_essence(c);
  }

  long int derived_value_calculator::compute_peripheral_essence       (const character::character& c) const
  {
    return calculator_workers.at(c.type())->compute_peripheral_essence(c);
  }

  long int derived_value_calculator::compute_spiritual_essence        (const character::character& c) const
  {
    return calculator_workers.at(c.type())->compute_spiritual_essence(c);
  }

  long int derived_value_calculator::compute_celestial_portion        (const character::character& c) const
  {
    return calculator_workers.at(c.type())->compute_celestial_portion(c);
  }

  unsigned int derived_value_calculator::compute_life_points              (const character::character& c) const
  {
    return calculator_workers.at(c.type())->compute_life_points(c);
  }

  unsigned int   derived_value_calculator::starting_khan                 (const character::creation::character_type& c) const
  {
    return calculator_workers.at(c)->starting_khan(c);
  }

  unsigned int derived_value_calculator::starting_essence                 (const character::creation::character_type& c) const
  {
    return calculator_workers.at(c)->starting_essence(c);
  }

  unsigned int derived_value_calculator::starting_logos                   (const character::creation::character_type& c) const
  {
    return calculator_workers.at(c)->starting_logos(c);
  }

  unsigned int derived_value_calculator::starting_willpower           (const character::character& c) const
  {
    return calculator_workers.at(c.type())->starting_willpower(c);
  }

  derived_value_calculator::~derived_value_calculator() {}
}
