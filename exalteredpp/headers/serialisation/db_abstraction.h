#pragma once

#include "character.h"
#include <QSharedPointer>

namespace serialisation {
  class db_abstraction
  {
  public:
    virtual QSharedPointer<character::character> load_character(const QString &character_name) = 0;
    virtual void save_character(const QSharedPointer<character::character> character) = 0;
    virtual QList<QString> get_character_names_list() = 0;

    virtual ~db_abstraction() {}
  };
}
