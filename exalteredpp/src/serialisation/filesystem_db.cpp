#include "filesystem_db.h"

#include <QDirIterator>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "characternotfoundexception.h"

namespace serialisation {

  using character::character;
  using namespace  character;

  filesystem_db::filesystem_db()
    : AVAILABLE_CHARACTERS_FILE("available_characters.json"), FILE_EXT(".dcg")
  {
    QFile map_file(AVAILABLE_CHARACTERS_FILE);
    if (map_file.exists())
      {
        try {
          map_file.open(QFile::ReadOnly);
          QString serialised_characters = map_file.readAll();
          map_file.close();
          QJsonDocument json_character = QJsonDocument::fromJson(serialised_characters.toUtf8());
          for (QString char_id : json_character.object().keys())
            {
              id_to_name.insert(char_id, json_character.object().value(char_id).toString());
            }

          if (id_to_name.empty())
            map_file.remove();
        }
        catch(...)
        {
          qDebug("Errors while loading character list!");
          map_file.remove();
        }
      }
  }

  void filesystem_db::remove_character(const std::string& character_id)
  {
    id_to_name.remove(character_id.c_str());
    save_character_map();
  }

  void filesystem_db::remove_character(unsigned int character_id)
  {
    remove_character(QString("character_%1").arg(character_id).toStdString());
  }

  bool filesystem_db::has_characters() const
  {
    return !id_to_name.empty();
  }

  std::shared_ptr<character> filesystem_db::load_character(const std::string& character_id)
  {
    if (!has_characters())
    {
      qDebug("expected file doesn't exist!");
      throw exception::character_not_found_exception();
    }

    QFile expected_file(QString(character_id.c_str()) + FILE_EXT);
    expected_file.open(QFile::ReadOnly);
    QString serialised_character = expected_file.readAll();
    expected_file.close();

    return std::make_shared<character>(serialised_character.toStdString());
  }

  std::shared_ptr<character> filesystem_db::create_character(const std::string& name,
                                                            const creation::character_type type,
                                                            const exalt::caste caste,
                                                            const attribute::attributes attributes,
                                                            const ability::abilities abilities,
                                                            const virtues::virtues virtues,
                                                            const power::power_container power_container)
  {
    unsigned int id = 0;

    int start_size = QString("character_").size();
    for (auto char_id: id_to_name.keys())
      {
        unsigned int new_id = static_cast<unsigned int>(char_id.mid(start_size, char_id.size() - start_size).toInt());
        if (new_id > id)
          id = new_id;
      }

    std::shared_ptr<character> result = std::make_shared<character>(name, type, caste, attributes, abilities, virtues, power_container, id + 1);
    return result;
  }

  std::vector<std::string> filesystem_db::character_list()
  {
    std::vector<std::string> result;
    for (auto name: id_to_name.keys())
      {
        result.push_back(name.toStdString());
      }

    return result;
  }

  std::string filesystem_db::character_name(const std::string& character_id) const
  {
    return id_to_name.value(character_id.c_str()).toStdString();
  }

  void filesystem_db::save_character_map()
  {
    QJsonObject character_list_object;
    for (std::string id : character_list())
      {
        character_list_object.insert(id.c_str(), id_to_name.value(id.c_str()));
      }
    save_json_to_file(QJsonDocument(character_list_object).toJson(), AVAILABLE_CHARACTERS_FILE);
  }

  void filesystem_db::save_character(std::shared_ptr<character>& character)
  {
    std::string serialisation = character->serialise();
    QString char_id = "character_" + QString::number(character->id());
    save_json_to_file(serialisation.c_str(), char_id + FILE_EXT);

    id_to_name.insert(char_id, character->get_name().c_str());
    save_character_map();
  }

  void filesystem_db::save_json_to_file(const QByteArray& json, const QString& filename) const
  {
    QFile expectedFile(filename);
    expectedFile.open(QFile::WriteOnly);
    expectedFile.write(json);
    expectedFile.close();
  }
}
