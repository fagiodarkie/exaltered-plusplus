#pragma once

#include "filesystem_db.h"
#include "managers/character_manager.h"

#include "derived_value_definitions.h"
#include "derived_value_calculator.h"

namespace dependency {
  static serialisation::filesystem_db s_db_abstraction;
  static manager::character_manager s_character_manager(s_db_abstraction);

  static calculator::derived_value_calculator derived_values(calculator::STANDARD_WORKER_MAP);
}

