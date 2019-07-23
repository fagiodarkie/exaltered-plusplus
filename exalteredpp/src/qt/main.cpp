#include "qt/exalteredapp.h"
#include <QApplication>

#include "filesystem_db.h"
#include "abilities/default_ability_factory.h"

int main(int argc, char *argv[])
{
  serialisation::filesystem_db s_db_abstraction;
  manager::character_manager s_character_manager(s_db_abstraction);

  QApplication a(argc, argv);
  ExalteredApp w(s_character_manager);
  w.show();
  return a.exec();
}
