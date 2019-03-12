#include "filesystem_db.h"

#include <QFile>

namespace serialisation {

  QString filesystem_db::FILE_EXT = ".dgc";

  filesystem_db::filesystem_db() {  }

  QString filesystem_db::normalise_name(const QString &name)
  {
    return name.toUtf8().simplified().replace(" ", "");
  }

  character::character filesystem_db::load_character(const QString& character_name) {
    QFile expectedFile(normalise_name(character_name) + FILE_EXT);
  }
}
