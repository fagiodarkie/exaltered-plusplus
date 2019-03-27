#pragma once

#include "character.h"
#include <QSharedPointer>

namespace serialisation {
  class db_abstraction
  {
  public:
    virtual QSharedPointer<character::character> load_character() = 0;
    virtual bool has_characters() const = 0;
    virtual QList<QSharedPointer<character::character>> character_list() = 0;
    virtual void save_character(const QSharedPointer<character::character> character) = 0;

    virtual ~db_abstraction() {}
  };
}
