#pragma once

#include <QSharedPointer>
#include "character.h"
#include "serialisation/db_abstraction.h"
#include "characternotfoundexception.h"
#include "qt-test/quick_chargen.h"

#define CHAR_MAN_TEST_CHAR_NAME "name"

namespace mock_tests {

  using character::character;
  using namespace character;

  class mock_db_abstraction: public serialisation::db_abstraction
  {
    // db_abstraction interface
  public:
    mock_db_abstraction() : has_character(true), cached_character(nullptr) {}

    std::shared_ptr<character> load_character(const QString& character_name)
    {
      if (has_character)
        return !cached_character ? generate_character_pointer(character_name, 0) : cached_character;
      throw exception::character_not_found_exception();
    }

    bool has_characters() const
    {
      return has_character;
    }

    void remove_character(const std::string& /*character_id*/)
    {
    }

    void remove_character(unsigned int /* character_id */) {}

    std::shared_ptr<character> create_character(const std::string name,
                                               const creation::character_type type,
                                               const exalt::caste caste,
                                               const attributes attributes,
                                               const abilities abilities,
                                               const virtues::virtues virtues,
                                               const power::power_container power_container)
    {
      has_character = true;
      return std::make_shared<character>(CHAR_MAN_TEST_CHAR_NAME, type, caste, attributes, abilities, virtues, power_container);
    }

    std::vector<std::string> character_list()
    {
      if (has_character) return { CHAR_MAN_TEST_CHAR_NAME } ;
      return {};
    }

    std::string character_name(const std::string& char_id) const
    {
      return char_id;
    }

    void save_character(const std::shared_ptr<character> character)
    {
      cached_character = character;
    }

    void mock_has_character(bool has_it)
    {
      has_character = has_it;
    }

  private:
    bool has_character;
    std::shared_ptr<character> cached_character;
  };

}
