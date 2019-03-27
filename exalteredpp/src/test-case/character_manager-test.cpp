#include "../thirdparty/catch/catch.hpp"

#include "errors/characternotfoundexception.h"
#include "managers/character_manager.h"

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
            ? QSharedPointer<character::character>(new character::character("CHARACTER_NAME"))
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

TEST_CASE("character_manager")
{
  QSharedPointer<character_manager_tests::mock_db_abstraction> mock = QSharedPointer<character_manager_tests::mock_db_abstraction>(new character_manager_tests::mock_db_abstraction());

  SECTION("should load character when it is present")
  {
    mock->mock_has_character(true);
    manager::character_manager sut = manager::character_manager(mock);
    QSharedPointer<character::character> result = sut.load_character();
    REQUIRE(result->get_name() == "CHARACTER_NAME");
  }

  SECTION("should load character when it is not present")
  {
    mock->mock_has_character(false);
    manager::character_manager sut = manager::character_manager(mock);
    QSharedPointer<character::character> result = sut.load_character();
    REQUIRE(result->get_name() != "CHARACTER_NAME");
  }

  SECTION("should save character without errors")
  {
    manager::character_manager sut = manager::character_manager(mock);
    try
    {
      QSharedPointer<character::character> to_save = QSharedPointer<character::character>(new character::character("CHARACTER_NAME"));
      sut.save_character(to_save);
      QSharedPointer<character::character> loaded = sut.load_character();
      REQUIRE(to_save->get_name() == loaded->get_name());
    }
    catch(...)
    {
      FAIL("Something went wrong while retrieving saved character");
    }
  }
}
