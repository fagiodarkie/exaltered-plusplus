#pragma once

#include <map>
#include "character.h"
#include "worker/abstract_calculator_worker.h"

namespace calculator {

  class derived_value_calculator : public worker::abstract_calculator_worker
  {
  public:
    typedef std::map<character::creation::character_type, std::shared_ptr<worker::abstract_calculator_worker>> worker_map;
    derived_value_calculator(worker_map initial_map);

    void calculate_with(character::creation::character_type character_type, std::shared_ptr<worker::abstract_calculator_worker> worker);

  private:
    worker_map calculator_workers;
  };

}
