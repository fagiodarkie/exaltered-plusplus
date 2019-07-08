#pragma once

#include "character.h"
#include "db_abstraction.h"
#include "abilities/abstract_ability_factory.h"

namespace manager {
  class character_manager
  {
  public:
    character_manager(QSharedPointer<serialisation::db_abstraction> db, QSharedPointer<character::abstract_ability_factory> ability_factory);

    QList<QPair<QString, QString>> characters() const;

    QSharedPointer<character::character> load_character(const QString& char_id = nullptr) const;
    QSharedPointer<character::character> create_character(const QString name,
                                                          const character::creation::character_type type,
                                                          const character::exalt::caste caste,
                                                          const character::attributes attributes,
                                                          const character::abilities abilities,
                                                          const character::virtues::virtues virtues,
                                                          const character::power::power_container power_container);
    void save_character(QSharedPointer<character::character> character) const;

  private:
    QSharedPointer<serialisation::db_abstraction> character_repository;
    QSharedPointer<character::abstract_ability_factory> ability_factory;
  };

}

