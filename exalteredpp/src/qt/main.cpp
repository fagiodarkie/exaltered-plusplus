#include "qt/exalteredapp.h"
#include "objects_factory.h"
#include <QApplication>

using namespace serialisation;
using namespace manager;
using namespace character;

int main(int argc, char *argv[])
{
  POINTER_TO(db_abstraction,            filesystem_db,             s_db_abstraction,     )
  POINTER_TO(abstract_ability_factory,  default_ability_factory,   s_ability_factory,    )
  POINTER_TO(character_manager,         character_manager,         s_character_manager,  s_db_abstraction, s_ability_factory)

  QApplication a(argc, argv);
  ExalteredApp w(s_character_manager.get());
  w.show();
  return a.exec();
}
