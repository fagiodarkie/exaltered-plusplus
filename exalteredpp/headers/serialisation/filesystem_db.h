#pragma once

#include "db_abstraction.h"

namespace serialisation {
  class filesystem_db : public db_abstraction
  {
  public:
    filesystem_db() = default;

    // db_abstraction interface
    QSharedPointer<character::character> load_character(const QString &character_name) override;
    void save_character(const character::character &character) override;
    QList<QString> get_character_names_list() override;

  private:
    static QString FILE_EXT;
    static QString normalise_name(const QString& name);
  };
}
