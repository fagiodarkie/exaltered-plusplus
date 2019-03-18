#include "filesystem_db.h"

#include <QFile>
#include <QJsonDocument>
#include <characternotfoundexception.h>

namespace serialisation {

  QString filesystem_db::FILE_EXT = ".dgc";

  QString filesystem_db::normalise_name(const QString &name)
  {
    return name.toUtf8().simplified().replace(" ", "");
  }

  QSharedPointer<character::character> filesystem_db::load_character(const QString& character_name)
  {
    QFile expectedFile(normalise_name(character_name) + FILE_EXT);
    if (!expectedFile.exists())
    {
      throw new exception::character_not_found_exception();
    }

    expectedFile.open(QFile::ReadOnly);
    QString serialised_character = expectedFile.readAll();
    expectedFile.close();
    QJsonDocument json_character = QJsonDocument::fromJson(serialised_character.toUtf8());

    return QSharedPointer<character::character>(new character::character(json_character.object()));
  }

  void filesystem_db::save_character(const QSharedPointer<character::character> character)
  {
    QJsonObject character_object;
    character->write(character_object);
    QJsonDocument document(character_object);

    QFile expectedFile(normalise_name(character->getName()) + FILE_EXT);
    expectedFile.open(QFile::WriteOnly);
    expectedFile.write(document.toBinaryData());
    expectedFile.close();
  }
}
