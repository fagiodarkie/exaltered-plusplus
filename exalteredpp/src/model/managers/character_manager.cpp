#include "managers/character_manager.h"

#include "characternotfoundexception.h"
#include "text/character_text_constants.h"

namespace manager {

  character_manager::character_manager(std::shared_ptr<serialisation::db_abstraction>& db, std::shared_ptr<character::abstract_ability_factory>& ability_factory)
    : character_repository(db), ability_factory(ability_factory)
  {
  }

  std::map<std::string, std::string> character_manager::characters() const
  {
    std::map<std::string, std::string> result;
    for (std::string character_id : character_repository->character_list())
      result[character_id] = character_repository->character_name(character_id);

    return result;
  }

  std::shared_ptr<character::character> character_manager::create_character(const std::string name, const character::creation::character_type type, const character::exalt::caste caste, const character::attributes attributes, const character::abilities abilities, const character::virtues::virtues virtues, const character::power::power_container power_container)
  {
    return character_repository->create_character(name,
                                                  type,
                                                  caste,
                                                  attributes,
                                                  abilities,
                                                  virtues,
                                                  power_container);
  }

  std::shared_ptr<character::character> character_manager::load_character(const std::string& char_id) const
  {
    if (!char_id.empty() && commons::contains(character_repository->character_list(), char_id))
        return character_repository->load_character(char_id);

    throw new exception::character_not_found_exception();
  }

  void character_manager::save_character(std::shared_ptr<character::character>& character) const
  {
    character_repository->save_character(character);
  }

}
