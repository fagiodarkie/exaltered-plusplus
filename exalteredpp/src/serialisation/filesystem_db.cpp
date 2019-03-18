#include "filesystem_db.h"

#include <QDirIterator>
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
      qDebug("expected file doesn't exist!");
      throw new exception::character_not_found_exception();
    }

    expectedFile.open(QFile::ReadOnly);
    QString serialised_character = expectedFile.readAll();
    expectedFile.close();
    QJsonDocument json_character = QJsonDocument::fromJson(serialised_character.toUtf8());

    return QSharedPointer<character::character>(new character::character(json_character.object()));
  }

  QList<QString> filesystem_db::get_character_names_list()
  {
    QList<QString> result;
    QDirIterator files_in_directory("");
    while (files_in_directory.hasNext())
    {
      QString next = files_in_directory.next();
      if (next.endsWith(FILE_EXT))
      {
        // TODO optimise system load
        QSharedPointer<character::character> found_character;
        try
        {
          QFileInfo file_info(next);
          found_character = load_character(file_info.completeBaseName());
          result.push_back(found_character->getName());
        }
        catch(...)
        {
          qDebug("got error during load of file");
        }
      }
    }

    return result;
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
