#pragma once

#include <QSharedPointer>
#include "character.h"
#include "serialisation/db_abstraction.h"

namespace character_manager_tests {

  class mock_db_abstraction: public serialisation::db_abstraction
  {
    // db_abstraction interface
  public:
    mock_db_abstraction() : has_character(true) {}

    QSharedPointer<character::character> load_character()
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

    QList<QSharedPointer<character::character>> character_list()
    {
      return {};
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
