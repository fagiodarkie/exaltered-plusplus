#include "managers/character_manager.h"

#include "characternotfoundexception.h"
#include "text/character_text_constants.h"

namespace manager {

  character_manager::character_manager(QSharedPointer<serialisation::db_abstraction> db, QSharedPointer<character::abstract_ability_factory> abilities)
    : character_repository(db), ability_factory(abilities)
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
      QSharedPointer<character::character> new_character(new character::character(model::text::character::DEFAULT_CHARACTER_NAME));

      for (character::ability_name ability : character::ABILITY_NAME.keys())
        {
          new_character->set_ability(ability, ability_factory->get_ability_group(ability));
        }

      save_character(new_character);
      return new_character;
    }
  }

  void character_manager::save_character(QSharedPointer<character::character> character) const
  {
    character_repository->save_character(character);
  }

}
