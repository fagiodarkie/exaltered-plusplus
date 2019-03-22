#include "filesystem_db.h"

#include <QDirIterator>
#include <QFile>
#include <QJsonDocument>

#include "characternotfoundexception.h"

namespace serialisation {

  QString filesystem_db::FILE_EXT = ".dgc";

  bool filesystem_db::has_characters() const
  {
    QFile expectedFile("character" + FILE_EXT);
    return expectedFile.exists();
  }

  QSharedPointer<character::character> filesystem_db::load_character()
  {
    if (!has_characters())
    {
      qDebug("expected file doesn't exist!");
      throw exception::character_not_found_exception();
    }

    QFile expectedFile("character" + FILE_EXT);
    expectedFile.open(QFile::ReadOnly);
    QString serialised_character = expectedFile.readAll();
    expectedFile.close();
    QJsonDocument json_character = QJsonDocument::fromJson(serialised_character.toUtf8());

    return QSharedPointer<character::character>(new character::character(json_character.object()));
  }

  QList<QSharedPointer<character::character>> filesystem_db::character_list()
  {
    return { load_character() };
  }

  void filesystem_db::save_character(const QSharedPointer<character::character> character)
  {
    QJsonObject character_object;
    character->write(character_object);
    QJsonDocument document(character_object);

    QFile expectedFile("character" + FILE_EXT);
    expectedFile.open(QFile::WriteOnly);
    expectedFile.write(document.toJson());
    expectedFile.close();
  }
}
