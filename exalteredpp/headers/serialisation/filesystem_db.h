#pragma once

#include "db_abstraction.h"

namespace serialisation {
  class filesystem_db : public db_abstraction
  {
  public:
    filesystem_db();

    // db_abstraction interface
    character::character load_character(const QString &character_name);
    void save_character(const QString &character_name, const character::character &character);
    QList<character::character> get_character_list();

  private:
    static QString FILE_EXT;
    static QString normalise_name(const QString& name);
  };
}
