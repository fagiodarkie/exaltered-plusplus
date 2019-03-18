#include "filesystem_db.h"

#include <QFile>
#include <QJsonDocument>
#include "error_codes.h"

namespace serialisation {

  QString filesystem_db::FILE_EXT = ".dgc";

  filesystem_db::filesystem_db() {  }

  QString filesystem_db::normalise_name(const QString &name)
  {
    return name.toUtf8().simplified().replace(" ", "");
  }

  character::character filesystem_db::load_character(const QString& character_name)
  {
    QFile expectedFile(normalise_name(character_name) + FILE_EXT);
    if (!expectedFile.exists())
      {
        throw new
      }

    expectedFile.open(QFile::ReadOnly);
    QString serialised_character = expectedFile.readAll();
    expectedFile.close();
    QJsonDocument json_character = QJsonDocument::fromJson(serialised_character.toUtf8());

    return character::character(json_character.object());
  }
}
