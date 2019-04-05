#include "../thirdparty/catch/catch.hpp"
#include <filesystem_db.h>
#include <QFile>
#include <QJsonDocument>
#include <QDirIterator>
#include "characternotfoundexception.h"

#define CHARACTER_NAME "He who Cries Silver Tears"

TEST_CASE("filesystem_db")
{
  serialisation::filesystem_db sut;

  SECTION("should save and load a character")
  {
    QSharedPointer<character::character> stub_character(new character::character(CHARACTER_NAME));
    sut.save_character(stub_character);
    REQUIRE(sut.character_list().size() == 1);
    QString id = sut.character_list().at(0);
    QSharedPointer<character::character> result = sut.load_character(id);
    REQUIRE(result->get_name() == CHARACTER_NAME);
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
    sut.save_character(QSharedPointer<character::character>(new character::character("name 2")));
    REQUIRE(sut.character_list().size() == 2);
  }

  SECTION("should retrieve a character's name")
  {
    sut.save_character(QSharedPointer<character::character>(new character::character("name 1")));
    QString id1 = sut.character_list().at(0);
    REQUIRE(sut.character_name(id1) == "name 1");
    sut.save_character(QSharedPointer<character::character>(new character::character("name 2")));
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
    new_sut.save_character(QSharedPointer<character::character>(new character::character("a")));
    new_sut.save_character(QSharedPointer<character::character>(new character::character("b")));
    new_sut.remove_character("a");
    REQUIRE(new_sut.character_list().size() == 1);
    REQUIRE_FALSE(new_sut.character_list().contains("a"));
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
