#include "filesystem_db.h"

#include <QDirIterator>
#include <QFile>
#include <QJsonDocument>

#include "characternotfoundexception.h"

namespace serialisation {

  QString filesystem_db::FILE_EXT = ".dgc";
  QString filesystem_db::AVAILABLE_CHARACTERS_FILE = "available_characters.json";

  bool filesystem_db::has_characters() const
  {
    return !id_to_name.empty();
  }

  QSharedPointer<character::character> filesystem_db::load_character(const QString& character_id)
  {
    if (!has_characters())
    {
      qDebug("expected file doesn't exist!");
      throw exception::character_not_found_exception();
    }

    QFile expectedFile(character_id + FILE_EXT);
    expectedFile.open(QFile::ReadOnly);
    QString serialised_character = expectedFile.readAll();
    expectedFile.close();
    QJsonDocument json_character = QJsonDocument::fromJson(serialised_character.toUtf8());

    return QSharedPointer<character::character>(new character::character(json_character.object()));
  }

  QList<QString> filesystem_db::character_list()
  {
    return id_to_name.keys();
  }

  QString filesystem_db::character_name(const QString& character_id) const
  {
    return id_to_name.value(character_id);
  }

  void filesystem_db::save_character(const QSharedPointer<character::character> character)
  {
    QJsonObject character_object;
    character->write_to_json(character_object);
    QString char_id = character->get_name().simplified();
    save_json_to_file(character_object, char_id + FILE_EXT);

    if (!character_list().contains(char_id))
      {
        id_to_name.insert(char_id, character->get_name());
        QJsonObject character_list_object;
        for (QString id : character_list())
          {
            character_list_object.insert(id, id_to_name.value(id));
          }
        save_json_to_file(character_list_object, AVAILABLE_CHARACTERS_FILE);
      }
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
