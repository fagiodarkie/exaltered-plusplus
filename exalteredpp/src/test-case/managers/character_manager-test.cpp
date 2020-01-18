#include "../thirdparty/catch/catch.hpp"

#include "errors/characternotfoundexception.h"
#include "managers/character_manager.h"
#include "db_abstraction_mock.h"
#include "calculator/worker/common_worker.h"
#include "qt-test/quick_chargen.h"

TEST_CASE("character_manager")
{
  mock_tests::mock_db_abstraction manager_mock;

  manager::character_manager sut = manager::character_manager(manager_mock);

  SECTION("should load character when it is present")
  {
    manager_mock.mock_has_character(true);
    std::shared_ptr<character::character> result = sut.load_character("name");
    REQUIRE(result->name() == CHAR_MAN_TEST_CHAR_NAME);
  }

  SECTION("should save character without errors")
  {
    try
    {
      std::shared_ptr<character::character> to_save = generate_character_pointer("name", 0);
      sut.save_character(to_save);
      std::shared_ptr<character::character> loaded = sut.load_character("name");
      REQUIRE(to_save->name() == loaded->name());
    }
    catch(...)
    {
      FAIL("Something went wrong while retrieving saved character");
    }
  }

  SECTION("should create a new character if requested")
  {
    try {
      auto attributes = attribute::attributes();
      attributes[attribute::attribute_enum::CONSTITUTION] = 2;
      auto generated = sut.create_character(calculator::worker::human_worker(), "name", character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, attributes, ability::abilities(), virtues::virtues(), power::essence(), power::willpower(), power::health(), power::logos());
      REQUIRE(generated);
    }
    catch(...)
    {
      FAIL("Something went wrong while generating character");
    }
  }

  SECTION("should list available characters")
  {
    manager_mock.mock_has_character(true);
    REQUIRE(sut.characters().size() > 0);
  }

  SECTION("will throw if a requested character id doesn't exist")
  {
    manager_mock.mock_has_character(true);
    REQUIRE_THROWS(sut.load_character("non_existing_character_id"));
  }
}
