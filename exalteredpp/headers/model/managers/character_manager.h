#pragma once

#include "character.h"
#include "db_abstraction.h"
#include "calculator/worker/abstract_calculator_worker.h"

namespace manager {
  class character_manager
  {
  public:
    character_manager(serialisation::db_abstraction& db);

    std::map<std::string, std::string> characters() const;

    std::shared_ptr<character::character> load_character(const std::string& char_id = nullptr) const;
    std::shared_ptr<character::character> create_character(const calculator::worker::abstract_calculator_worker& starting_values_calculator,
                                                          const std::string name,
                                                          const character::creation::character_type type,
                                                          const character::exalt::caste caste,
                                                          const character::attributes attributes,
                                                          const character::abilities abilities,
                                                          const character::virtues::virtues virtues,
                                                          const character::power::power_container power_container);
    void save_character(std::shared_ptr<character::character>& character) const;

  private:
    serialisation::db_abstraction& character_repository;
  };

}

