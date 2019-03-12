#pragma once

#include "character.h"
#include <QSharedPointer>

namespace serialisation {
  class db_abstraction
  {
  public:
    virtual character::character load_character(const QString& character_name) = 0;
    virtual void save_character(const QString& character_name, const character::character& character) = 0;
    virtual QList<character::character> get_character_list() = 0;

    virtual ~db_abstraction() {}
  };

  static QSharedPointer<db_abstraction> db;
}
