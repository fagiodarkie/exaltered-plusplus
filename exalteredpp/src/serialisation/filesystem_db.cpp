#include "filesystem_db.h"

#include <QFile>

namespace serialisation {

  QString filesystem_db::FILE_EXT = ".dgc";

  QString filesystem_db::normalise_name(const QString &name)
  {
    return name.toUtf8().simplified().replace(" ", "");
  }

  QSharedPointer<character::character> filesystem_db::load_character(const QString& character_name) {
    QFile expectedFile(normalise_name(character_name) + FILE_EXT);
    QSharedPointer<character::character> result(new character::character("test"));
    return result;
  }

  QList<QString> filesystem_db::get_character_names_list()
  {
    return QList<QString>({"test"});
  }

  void filesystem_db::save_character(const character::character &character)
  {
    // TODO
  }
}
