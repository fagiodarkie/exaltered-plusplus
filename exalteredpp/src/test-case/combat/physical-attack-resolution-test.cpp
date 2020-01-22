#include "../thirdparty/catch/catch.hpp"

#include "combat/physical_attack.h"
#include "character.h"
#include "derived_value_calculator.h"
#include "worker/exalt_worker.h"
#include "diceroller_mock.h"
#include <memory>

TEST_CASE("Physical Attack Resolution")
{
  auto attack_character = std::make_shared<character::character>("");
  attack_character->set_type(character::creation::TYPE_MORTAL_HERO);
  attack_character->set(attribute::attribute_enum::STRENGTH, 3);
  attack_character->set(attribute::attribute_enum::DEXTERITY, 4);
  attack_character->set(ability::ability_enum::DODGE, 4);
  attack_character->set(ability::ability_enum::THROWN, 3);
  attack_character->set(ability::ability_enum::MELEE, 3);

  combat::weapon attack_weapon;
  attack_weapon.use_with(ability::ability_enum::THROWN)
      .with_precision(5)
      .with_base_damage(3)
      .with_damage_type(combat::damage_type_enum::LETHAL)
      .uses_for_damage(attribute::attribute_enum::STRENGTH)
      .requires_for_precision(attribute::attribute_enum::DEXTERITY);

  calculator::derived_value_calculator::worker_map worker_map = {
    { character::creation::TYPE_MORTAL_HERO, std::make_shared<calculator::worker::human_worker>() }
  };
  auto value_calculator = calculator::derived_value_calculator(worker_map);

  auto roller = std::make_shared<mock_diceroller>();
  roller->set_ratio(0.5);

  SECTION("Should give a \"fail\" outcome if precision doesn't pass VD")
  {
    auto precision = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 10, 10);
    auto vd_comparison = precision.with_successes(5);
    REQUIRE_FALSE(vd_comparison.hits());
  }

  SECTION("Should take into account precision maluses")
  {
    // 7 dice - 2 successes should not hit
    auto vd_comparison_failure = combat::attack_declaration::declare()
        .declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 10, 10)
        .precision(10).internal_malus(3).malus(2)
        .apply(roller);
    REQUIRE_FALSE(vd_comparison_failure.hits());
  }

  SECTION("Should take into account precision bonuses")
  {
    // 16 dice + 4 successes should hit
    auto vd_comparison = combat::attack_declaration::declare()
        .declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 10, 10)
        .precision(10).internal_bonus(6).bonus(4)
        .apply(roller);
    REQUIRE(vd_comparison.hits());
  }

  SECTION("should take into account weapon stats")
  {
    roller->set_ratio(1);
    auto vd_comparison = combat::attack_declaration::declare()
        // precision is 7, weapon precision is 5 => 12 dice. We'll have them all rolling 7s
        .attacker(attack_character).with(attack_weapon)
        .declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 10, 10)
        .apply(roller);
    REQUIRE(vd_comparison.hits());

    // now we make it fail
    roller->set_ratio(0.3);
    auto vd_comparison_fail = combat::attack_declaration::declare()
        // precision is 7, weapon precision is 5 => 12 dice. We'll have them all rolling 7s
        .attacker(attack_character).with(attack_weapon)
        .declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 10, 10)
        .apply(roller);
    REQUIRE_FALSE(vd_comparison_fail.hits());
  }
}
