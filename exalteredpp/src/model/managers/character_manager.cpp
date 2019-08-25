#include "managers/character_manager.h"

#include "characternotfoundexception.h"
#include "text/character_text_constants.h"

namespace manager {

  character_manager::character_manager(serialisation::db_abstraction& db)
    : character_repository(db)
  {
  }

  std::map<std::string, std::string> character_manager::characters() const
  {
    std::map<std::string, std::string> result;
    for (std::string character_id : character_repository.character_list())
      result[character_id] = character_repository.character_name(character_id);

    return result;
  }

  std::shared_ptr<character::character> character_manager::create_character(const calculator::worker::abstract_calculator_worker& calculator, const std::string name, const character::creation::character_type type, const character::exalt::caste caste, const character::attributes attributes, const character::abilities abilities, const character::virtues::virtues virtues, const character::power::power_container power_container)
  {
    // finishing touches for the character
    power_container.get_logos().set_logos(calculator.starting_logos(type));
    power_container.get_essence().set_khan(calculator.starting_khan(type));
    // will have to be changed when we introduce bonus points
    power_container.get_essence().set_permanent_essence(calculator.starting_essence(type));


    auto final_character = character_repository.create_character(name,
                                                  type,
                                                  caste,
                                                  attributes,
                                                  abilities,
                                                  virtues,
                                                  power_container);

    final_character->get_essence().set_celestial_portion(calculator.compute_celestial_portion(*final_character));
    final_character->get_essence().set_total_personal_essence(calculator.compute_personal_essence(*final_character));
    final_character->get_essence().set_total_peripheral_essence(calculator.compute_peripheral_essence(*final_character));
    final_character->get_essence().set_total_spiritual_essence(calculator.compute_spiritual_essence(*final_character));
    final_character->get_willpower().set_permanent_willpower(calculator.starting_willpower(*final_character));
    final_character->get_willpower().restore(final_character->get_willpower().permanent_willpower());
    final_character->get_health().set_total_health(calculator.compute_life_points(*final_character));

    return final_character;
  }

  std::shared_ptr<character::character> character_manager::load_character(const std::string& char_id) const
  {
    if (!char_id.empty() && commons::contains(character_repository.character_list(), char_id))
        return character_repository.load_character(char_id);

    throw new exception::character_not_found_exception();
  }

  void character_manager::save_character(std::shared_ptr<character::character>& character) const
  {
    character_repository.save_character(character);
  }

}
