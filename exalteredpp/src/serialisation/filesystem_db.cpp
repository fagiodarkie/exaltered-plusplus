#include "filesystem_db.h"

#include <QDirIterator>
#include <QFile>
#include <QJsonDocument>

#include "characternotfoundexception.h"

namespace serialisation {

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

  void filesystem_db::remove_character(const QString& character_id)
  {
    id_to_name.remove(character_id);
    save_character_map();
  }

  void filesystem_db::remove_character(unsigned int character_id)
  {
    remove_character(QString("character_") + QString::number(character_id));
  }

  bool filesystem_db::has_characters() const
  {
    return !id_to_name.empty();
  }

  QSharedPointer<character> filesystem_db::load_character(const QString& character_id)
  {
    if (!has_characters())
    {
      qDebug("expected file doesn't exist!");
      throw exception::character_not_found_exception();
    }

    QFile expected_file(character_id + FILE_EXT);
    expected_file.open(QFile::ReadOnly);
    QString serialised_character = expected_file.readAll();
    expected_file.close();
    QJsonDocument json_character = QJsonDocument::fromJson(serialised_character.toUtf8());

    return QSharedPointer<character>(new character(json_character.object()));
  }

  QSharedPointer<character> filesystem_db::create_character(const QString name,
                                                            const creation::character_type type,
                                                            const exalt::caste caste,
                                                            const attributes attributes,
                                                            const abilities abilities,
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

    QSharedPointer<character> result(new character(name, type, caste, attributes, abilities, virtues, power_container, id + 1));
    return result;
  }

  QList<QString> filesystem_db::character_list()
  {
    return id_to_name.keys();
  }

  QString filesystem_db::character_name(const QString& character_id) const
  {
    return id_to_name.value(character_id);
  }

  void filesystem_db::save_character_map()
  {
    QJsonObject character_list_object;
    for (QString id : character_list())
      {
        character_list_object.insert(id, id_to_name.value(id));
      }
    save_json_to_file(character_list_object, AVAILABLE_CHARACTERS_FILE);
  }

  void filesystem_db::save_character(const QSharedPointer<character> character)
  {
    QJsonObject character_object;
    character->write_to_json(character_object);
    QString char_id = "character_" + QString::number(character->id());
    save_json_to_file(character_object, char_id + FILE_EXT);

    id_to_name.insert(char_id, character->get_name());
    save_character_map();
  }

  void filesystem_db::save_json_to_file(QJsonObject json, const QString& filename) const
  {
    QJsonDocument document(json);
    QFile expectedFile(filename);
    expectedFile.open(QFile::WriteOnly);
    expectedFile.write(document.toJson());
    expectedFile.close();
  }
}
