#pragma once

#include "character.h"
#include "db_abstraction.h"
#include "abilities/abstract_ability_factory.h"

namespace manager {
  class character_manager
  {
  public:
    character_manager(QSharedPointer<serialisation::db_abstraction> db, QSharedPointer<character::abstract_ability_factory> ability_factory);

    QSharedPointer<character::character> load_character(const QString& char_id) const;
    void save_character(QSharedPointer<character::character> character) const;

  private:
    QSharedPointer<serialisation::db_abstraction> character_repository;
    QSharedPointer<character::abstract_ability_factory> ability_factory;
  };

}

