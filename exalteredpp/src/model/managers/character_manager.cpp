#include "managers/character_manager.h"

#include "characternotfoundexception.h"
#include "text/character_text_constants.h"

namespace manager {

  character_manager::character_manager(QSharedPointer<serialisation::db_abstraction> db)
    : character_repository(db)
  {
  }

  QSharedPointer<character::character> character_manager::load_character() const
  {
    try
    {
      return character_repository->load_character();
    }
    catch (exception::character_not_found_exception& e)
    {
      qDebug(e.what());
      return QSharedPointer<character::character>(new character::character(model::text::character::DEFAULT_CHARACTER_NAME));
    }
  }

}
