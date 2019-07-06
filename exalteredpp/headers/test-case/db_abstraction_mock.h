#pragma once

#include <QSharedPointer>
#include "character.h"
#include "serialisation/db_abstraction.h"
#include "characternotfoundexception.h"

#define CHAR_MAN_TEST_CHAR_NAME "CHARACTER_NAME"

namespace mock_tests {

  using character::character;
  using namespace character;

  class mock_db_abstraction: public serialisation::db_abstraction
  {
    // db_abstraction interface
  public:
    mock_db_abstraction() : has_character(true) {}

    QSharedPointer<character> load_character(const QString& /*character_id*/)
    {
      if (has_character)
        return cached_character;
      throw exception::character_not_found_exception();
    }

    bool has_characters() const
    {
      return has_character;
    }

    void remove_character(const QString& /*character_id*/)
    {
    }

    void remove_character(unsigned int /* character_id */) {}

    QSharedPointer<character> create_character( const QString name,
                                                           const creation::character_type type,
                                                           const exalt::caste caste,
                                                           const attributes attributes,
                                                           const abilities abilities,
                                                           const virtues::virtues virtues,
                                                           const power::power_container power_container)
    {
      has_character = true;
      return QSharedPointer<character>(new character(CHAR_MAN_TEST_CHAR_NAME, type, caste, attributes, abilities, virtues, power_container));
    }

    QList<QString> character_list()
    {
      if (has_character) return {CHAR_MAN_TEST_CHAR_NAME} ;
      return {};
    }

    QString character_name(const QString& char_id) const
    {
      return char_id;
    }

    void save_character(const QSharedPointer<character> character)
    {
      cached_character = character;
    }

    void mock_has_character(bool has_it)
    {
      has_character = has_it;
    }

  private:
    bool has_character;
    QSharedPointer<character> cached_character;
  };

}
