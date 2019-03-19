#include "../thirdparty/catch/catch.hpp"

#include "errors/characternotfoundexception.h"
#include "managers/character_manager.h"

class mock_db_abstraction: public serialisation::db_abstraction
{
  // db_abstraction interface
public:
  mock_db_abstraction() : has_character(true) {}

  QSharedPointer<character::character> load_character()
  {
    if (has_character)
      return QSharedPointer<character::character>(new character::character("CHARACTER_NAME"));
    throw exception::character_not_found_exception();
  }

  bool has_characters() const
  {
    return has_character;
  }

  void save_character(const QSharedPointer<character::character> character) {}

  void mock_has_character(bool has_it)
  {
    has_character = has_it;
  }

private:
  bool has_character;
};

TEST_CASE("character_manager")
{
  SECTION("should load character when it is present")
  {
    QSharedPointer<mock_db_abstraction> mock = QSharedPointer<mock_db_abstraction>(new mock_db_abstraction());
    mock->mock_has_character(true);
    manager::character_manager sut = manager::character_manager(mock);
    QSharedPointer<character::character> result = sut.load_character();
    REQUIRE(result->get_name() == "CHARACTER_NAME");
  }

  SECTION("should load character when it is not present")
  {
    QSharedPointer<mock_db_abstraction> mock = QSharedPointer<mock_db_abstraction>(new mock_db_abstraction());
    mock->mock_has_character(false);
    manager::character_manager sut = manager::character_manager(mock);
    QSharedPointer<character::character> result = sut.load_character();
    REQUIRE(result->get_name() != "CHARACTER_NAME");
  }
}
