#pragma once

#include "character.h"
#include "db_abstraction.h"

namespace manager {
  class character_manager
  {
  public:
    character_manager(QSharedPointer<serialisation::db_abstraction> db);

    QSharedPointer<character::character> load_character() const;

  private:
    QSharedPointer<serialisation::db_abstraction> character_repository;
  };

}

