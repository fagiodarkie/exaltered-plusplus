#include "../thirdparty/catch/catch.hpp"
#include <filesystem_db.h>
#include <QFile>
#include "characternotfoundexception.h"

#define CHARACTER_NAME "He who Cries Silver Tears"

TEST_CASE("filesystem_db")
{
  serialisation::filesystem_db sut;

  // remove the filesystem_db character file
  QFile char_file("character.dgc");
  if (char_file.exists())
  {
    char_file.remove();
  }

  SECTION("should save and load a character")
  {
    QSharedPointer<character::character> stub_character(new character::character(CHARACTER_NAME));
    sut.save_character(stub_character);
    QSharedPointer<character::character> result = sut.load_character();
    REQUIRE(result->get_name() == CHARACTER_NAME);
  }

  SECTION("should throw an exception if the file isn't there")
  {
    try {
      sut.load_character();
    } catch (QException& e) {
      REQUIRE(dynamic_cast<exception::character_not_found_exception*>(&e) != nullptr);
    }
  }
}
