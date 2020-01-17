#include "../thirdparty/catch/catch.hpp"
#include <filesystem_db.h>
#include <QFile>
#include <QJsonDocument>
#include <QDirIterator>
#include "characternotfoundexception.h"
#include "qt-test/quick_chargen.h"
#include <QJsonObject>
#include "common/reverse_search.h"

TEST_CASE("filesystem_db")
{
  serialisation::filesystem_db sut;
  std::shared_ptr<character::character> stub = generate_character_pointer("stub", 0);

  SECTION("should save and load a character")
  {
    sut.save_character(stub);
    REQUIRE(sut.character_list().size() == 1);
    QString id = sut.character_list().at(0).c_str();
    std::shared_ptr<character::character> result = sut.load_character(id.toStdString());
    REQUIRE(result->name() == stub->name());
  }

  SECTION("should throw an exception if the file isn't there")
  {
    try {
      sut.load_character("non existing character");
    } catch (std::exception& e) {
      REQUIRE(dynamic_cast<exception::character_not_found_exception*>(&e) != nullptr);
    }
  }

  SECTION("should add multiple characters")
  {
    REQUIRE(sut.character_list().empty());
    auto c1 = generate_character_pointer("stub", 0),
        c2 = generate_character_pointer("stub", 1);
    sut.save_character(c1);
    REQUIRE(sut.character_list().size() == 1);
    sut.save_character(c2);
    REQUIRE(sut.character_list().size() == 2);
  }

  SECTION("should retrieve a character's name")
  {
    QString name1 = "name1", name2 = "name2";
    auto c1 = generate_character_pointer(name1, 0),
        c2 = generate_character_pointer(name2, 1);
    sut.save_character(c1);
    QString id1 = sut.character_list().at(0).c_str();
    REQUIRE(sut.character_name(id1.toStdString()).c_str() == name1);
    sut.save_character(c2);
    QString id2 = sut.character_list().at(1).c_str();
    REQUIRE(sut.character_name(id1.toStdString()).c_str() == name1);
    REQUIRE(sut.character_name(id2.toStdString()).c_str() == name2);
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
    auto  a_char = generate_character_pointer("a", 0),
          b_char = generate_character_pointer("b", 1);
    new_sut.save_character(a_char);
    new_sut.save_character(b_char);
    new_sut.remove_character(a_char->id());
    REQUIRE(new_sut.character_list().size() == 1);
    REQUIRE_FALSE(commons::contains(new_sut.character_list(), std::string("character_0")));
    REQUIRE(commons::contains(new_sut.character_list(), std::string("character_1")));
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
    std::shared_ptr<character::character> a_character(generate_character_pointer("a", 1));
    sut.save_character(a_character);
    a_character->set_name("b");
    sut.save_character(a_character);
    REQUIRE(sut.character_list().size() == 1);
    REQUIRE(sut.character_list().at(0) == "character_1");
  }

  SECTION("should create a new character with a new id")
  {
    auto new_char = sut.create_character("name", character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, attribute::attributes(), ability::abilities(), virtues::virtues(), power::essence(), power::willpower(), power::health(), power::logos());
    sut.save_character(new_char);
    auto new_char_with_strange_id = sut.create_character("name", character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, attribute::attributes(), ability::abilities(), virtues::virtues(), power::essence(), power::willpower(), power::health(), power::logos());
    auto new_char_2 = sut.create_character("name", character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, attribute::attributes(), ability::abilities(), virtues::virtues(), power::essence(), power::willpower(), power::health(), power::logos());
    CHECK(new_char_2->id() == new_char_with_strange_id->id());
    sut.save_character(new_char_2);
    REQUIRE(sut.character_list().size() == 2);
    REQUIRE(new_char->id() < new_char_2->id());
    sut.save_character(new_char_with_strange_id);
    REQUIRE(sut.character_list().size() == 2);
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
