#include "dependencies.h"

namespace dependency {
  const std::shared_ptr<dice::dice_roller <dice::bashing_brutal   , dice::mortal_10_rule>> dice_rollers::BASHING_DAMAGE_ROLLER
    = std::make_shared<dice::dice_roller  <dice::bashing_brutal   , dice::mortal_10_rule>>();

  const std::shared_ptr<dice::dice_roller <dice::lethal_brutal    , dice::mortal_10_rule>> dice_rollers::LETHAL_DAMAGE_ROLLER
    = std::make_shared<dice::dice_roller  <dice::lethal_brutal    , dice::mortal_10_rule>>();
  const std::shared_ptr<dice::dice_roller <dice::aggravated_brutal, dice::mortal_10_rule>> dice_rollers::AGGRAVATED_DAMAGE_ROLLER
    = std::make_shared<dice::dice_roller  <dice::aggravated_brutal, dice::mortal_10_rule>>();

  const std::shared_ptr<dice::dice_roller <dice::no_brutal        , dice::mortal_10_rule>> dice_rollers::MORTAL_POOL_ROLLER
    = std::make_shared<dice::dice_roller  <dice::no_brutal        , dice::mortal_10_rule>>();
  const std::shared_ptr<dice::dice_roller <dice::no_brutal        , dice::exalt_10_rule<>>> dice_rollers::EXALT_POOL_ROLLER
    = std::make_shared<dice::dice_roller  <dice::no_brutal        , dice::exalt_10_rule<>>>();


  const std::shared_ptr<combat::body_part_roller> dice_rollers::BODY_PART_ROLLER = std::make_shared<combat::body_part_roller>();


  const std::shared_ptr<dice::abstract_dice_roller>  dice_rollers::damage_roller(combat::damage_type_enum damage_type)
  {
    switch (damage_type) {
      case combat::damage_type_enum::BASHING: return BASHING_DAMAGE_ROLLER;
      case combat::damage_type_enum::LETHAL: return LETHAL_DAMAGE_ROLLER;
      case combat::damage_type_enum::AGGRAVATED: return AGGRAVATED_DAMAGE_ROLLER;
    }
    return BASHING_DAMAGE_ROLLER;
  }

  const std::shared_ptr<dice::abstract_dice_roller>  dice_rollers::pool_roller(character::creation::character_type character_type)
  {
    bool is_supernatural = character::creation::character_type_model::get_by_character_type(character_type).is_supernatural;

    if (is_supernatural) return EXALT_POOL_ROLLER;

    return MORTAL_POOL_ROLLER;
  }

  const std::shared_ptr<combat::body_part_roller>    dice_rollers::body_part_roller()
  {
    return BODY_PART_ROLLER;
  }
}
