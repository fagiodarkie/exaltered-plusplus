#pragma once

#include <QSharedPointer>
#include "character.h"
#include "serialisation/db_abstraction.h"
#include "characternotfoundexception.h"

#define CHAR_MAN_TEST_CHAR_NAME "CHARACTER_NAME"

namespace mock_tests {

  class mock_db_abstraction: public serialisation::db_abstraction
  {
    // db_abstraction interface
  public:
    mock_db_abstraction() : has_character(true) {}

    QSharedPointer<character::character> load_character(const QString& /*character_id*/)
    {
      if (has_character)
        return cached_character.isNull()
            ? QSharedPointer<character::character>(new character::character(CHAR_MAN_TEST_CHAR_NAME))
            : cached_character;
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

    QSharedPointer<character::character> create_character(const QString& /*character_id*/)
    {
      has_character = true;
      return QSharedPointer<character::character>(new character::character(CHAR_MAN_TEST_CHAR_NAME));
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

    void save_character(const QSharedPointer<character::character> character)
    {
      cached_character = character;
    }

    void mock_has_character(bool has_it)
    {
      has_character = has_it;
    }

  private:
    bool has_character;
    QSharedPointer<character::character> cached_character;
  };

}
