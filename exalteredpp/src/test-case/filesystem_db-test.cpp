#include "../thirdparty/catch/catch.hpp"
#include <filesystem_db.h>
#include <QFile>
#include <QJsonDocument>
#include <QDirIterator>
#include "characternotfoundexception.h"

TEST_CASE("filesystem_db")
{
  serialisation::filesystem_db sut;

  SECTION("should save and load a character")
  {
    QSharedPointer<character::character> stub_character(new character::character("name", 0));
    sut.save_character(stub_character);
    REQUIRE(sut.character_list().size() == 1);
    QString id = sut.character_list().at(0);
    QSharedPointer<character::character> result = sut.load_character(id);
    REQUIRE(result->get_name() == "name");
  }

  SECTION("should throw an exception if the file isn't there")
  {
    try {
      sut.load_character("non existing character");
    } catch (QException& e) {
      REQUIRE(dynamic_cast<exception::character_not_found_exception*>(&e) != nullptr);
    }
  }

  SECTION("should add multiple characters")
  {
    REQUIRE(sut.character_list().isEmpty());
    sut.save_character(QSharedPointer<character::character>(new character::character("name 1")));
    REQUIRE(sut.character_list().size() == 1);
    sut.save_character(QSharedPointer<character::character>(new character::character("name 2", 1)));
    REQUIRE(sut.character_list().size() == 2);
  }

  SECTION("should retrieve a character's name")
  {
    sut.save_character(QSharedPointer<character::character>(new character::character("name 1")));
    QString id1 = sut.character_list().at(0);
    REQUIRE(sut.character_name(id1) == "name 1");
    sut.save_character(QSharedPointer<character::character>(new character::character("name 2", 1)));
    QString id2 = sut.character_list().at(1);
    REQUIRE(sut.character_name(id1) == "name 1");
    REQUIRE(sut.character_name(id2) == "name 2");
  }

  SECTION("should load characters list")
  {
    QJsonObject data;
    data.insert("id", "name");
    QJsonDocument document_data;
    document_data.setObject(data);
    QFile char_file("available_characters.json");
    char_file.open(QFile::WriteOnly);
    char_file.write(document_data.toJson());
    char_file.close();

    serialisation::filesystem_db new_sut;
    REQUIRE(new_sut.character_list().size() == 1);
    REQUIRE(new_sut.character_list().at(0) == "id");
    REQUIRE(new_sut.character_name("id") == "name");
  }

  SECTION("should load characters list")
  {
    serialisation::filesystem_db new_sut;
    auto  a_char = QSharedPointer<character::character>(new character::character("a", 0)),
          b_char = QSharedPointer<character::character>(new character::character("b", 1));
    new_sut.save_character(a_char);
    new_sut.save_character(b_char);
    new_sut.remove_character(a_char->id());
    REQUIRE(new_sut.character_list().size() == 1);
    REQUIRE_FALSE(new_sut.character_list().contains("character_0"));
    REQUIRE(new_sut.character_list().contains("character_1"));
  }

  SECTION("should not load if data file is corrupted")
  {
    QFile char_file("available_characters.json");
    char_file.open(QFile::WriteOnly);
    char_file.write("garbage");
    char_file.close();

    serialisation::filesystem_db new_sut;
    REQUIRE(new_sut.character_list().size() == 0);
    REQUIRE_FALSE(char_file.exists());
  }

  SECTION("should remove old character file when character name changes")
  {
    QSharedPointer<character::character> a_character(new character::character("a", 1));
    sut.save_character(a_character);
    a_character->set_name("b");
    sut.save_character(a_character);
    REQUIRE(sut.character_list().size() == 1);
    REQUIRE(sut.character_list().at(0) == "character_1");
  }

  // remove the filesystem_db character files
  QFile char_file("available_characters.json");
  if (char_file.exists())
  {
    char_file.remove();
  }

  QStringList character_files("*.dcg");
  QDir directory;
  for (QString character_file : directory.entryList(character_files))
    {
      QFile tbdeleted(character_file);
      tbdeleted.remove();
    }

}
