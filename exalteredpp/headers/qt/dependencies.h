#pragma once

#include "filesystem_db.h"
#include "managers/character_manager.h"

#include "derived_value_definitions.h"
#include "derived_value_calculator.h"
#include "character/creation/character_type_model.h"

#include "dice_roller/dice_roller.h"

namespace dependency {
  static serialisation::filesystem_db s_db_abstraction;
  static manager::character_manager s_character_manager(s_db_abstraction);

  static calculator::derived_value_calculator derived_values(calculator::STANDARD_WORKER_MAP);

  class dice_rollers {

  public:
    static const std::shared_ptr<dice::abstract_dice_roller>  damage_roller(combat::damage_type_enum damage_type);

    static const std::shared_ptr<dice::abstract_dice_roller>  pool_roller(character::creation::character_type character_type);

    static const std::shared_ptr<combat::body_part_roller>    body_part_roller();

  private:

    const static std::shared_ptr<dice::dice_roller<dice::bashing_brutal, dice::mortal_10_rule>> BASHING_DAMAGE_ROLLER;
    const static std::shared_ptr<dice::dice_roller<dice::lethal_brutal , dice::mortal_10_rule>> LETHAL_DAMAGE_ROLLER;
    const static std::shared_ptr<dice::dice_roller<dice::aggravated_brutal, dice::mortal_10_rule>> AGGRAVATED_DAMAGE_ROLLER;

    const static std::shared_ptr<dice::dice_roller<dice::no_brutal, dice::mortal_10_rule>> MORTAL_POOL_ROLLER;
    const static std::shared_ptr<dice::dice_roller<dice::no_brutal, dice::exalt_10_rule<>>> EXALT_POOL_ROLLER;

    const static std::shared_ptr<combat::body_part_roller> BODY_PART_ROLLER;
  };

}

