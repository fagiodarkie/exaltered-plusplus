#include "managers/character_manager.h"

#include "characternotfoundexception.h"
#include "text/character_text_constants.h"

namespace manager {

  character_manager::character_manager(QSharedPointer<serialisation::db_abstraction> db, QSharedPointer<character::abstract_ability_factory> abilities)
    : character_repository(db), ability_factory(abilities)
  {
  }

  QList<QPair<QString, QString>> character_manager::characters() const
  {
    QList<QPair<QString, QString>> result;
    for (QString character_id : character_repository->character_list())
      result.push_back(QPair<QString, QString>(character_id, character_repository->character_name(character_id)));

    return result;
  }

  QSharedPointer<character::character> character_manager::load_character(const QString& char_id) const
  {
    if (char_id != nullptr && character_repository->character_list().contains(char_id))
        return character_repository->load_character(char_id);

    QSharedPointer<character::character> new_character = character_repository->create_character(model::text::character::DEFAULT_CHARACTER_NAME);

    for (character::ability_names::ability_name ability : character::ability_names::ABILITY_NAME.keys())
      {
        new_character->set_ability(ability, ability_factory->get_ability_group(ability));
      }

    save_character(new_character);
    return new_character;
  }

  void character_manager::save_character(QSharedPointer<character::character> character) const
  {
    character_repository->save_character(character);
  }

}
