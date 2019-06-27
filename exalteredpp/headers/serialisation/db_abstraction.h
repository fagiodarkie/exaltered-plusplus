#pragma once

#include "character.h"
#include <QSharedPointer>

namespace serialisation {

  using character::character;
  using namespace character;

  class db_abstraction
  {
  public:
    virtual QSharedPointer<character> load_character(const QString& character_id) = 0;
    virtual bool has_characters() const = 0;
    virtual QList<QString> character_list() = 0;
    virtual QString character_name(const QString& character_id) const = 0;
    virtual void remove_character(const QString& character_id) = 0;
    virtual void remove_character(unsigned int character_id) = 0;
    virtual void save_character(const QSharedPointer<character> character) = 0;
    virtual QSharedPointer<character> create_character( const QString name,
                                                        const creation::character_type type,
                                                        const exalt::caste caste,
                                                        const attributes attributes,
                                                        const abilities abilities,
                                                        const virtues::virtues virtues,
                                                        const power::power_container power_container) = 0;

    virtual ~db_abstraction() {}
  };
}
