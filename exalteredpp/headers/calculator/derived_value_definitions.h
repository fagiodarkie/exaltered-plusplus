#pragma once

#include "worker/exalt_worker.h"

namespace calculator {

  static const std::shared_ptr<calculator::worker::abstract_calculator_worker> human = std::make_shared<calculator::worker::human_worker>();
  static const std::shared_ptr<calculator::worker::abstract_calculator_worker> exalt = std::make_shared<calculator::worker::exalt_worker>();

  static const std::map<character::creation::character_type, std::shared_ptr<calculator::worker::abstract_calculator_worker>> STANDARD_WORKER_MAP = {
    { character::creation::TYPE_MORTAL_EXTRA     , human },
    { character::creation::TYPE_MORTAL_HERO      , human },
    { character::creation::TYPE_SOLAR_EXALT      , exalt },
    { character::creation::TYPE_ABYSSAL_EXALT    , exalt },
    { character::creation::TYPE_INFERNAL_EXALT   , exalt },
    { character::creation::TYPE_TERRESTRIAL_EXALT, exalt }
  };

}
