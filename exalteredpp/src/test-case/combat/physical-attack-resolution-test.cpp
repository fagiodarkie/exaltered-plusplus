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
  attack_character->set(attribute::attribute_enum::CONSTITUTION, 2);
  attack_character->set(ability::ability_enum::DODGE, 4);
  attack_character->set(ability::ability_enum::THROWN, 3);
  attack_character->set(ability::ability_enum::MELEE, 3);

  auto defense_character = std::make_shared<character::character>(attack_character->serialise());

  equip::weapon attack_weapon;
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

  SECTION("Declaration should take into account both and only weapon and attack attributes")
  {
    auto declaration = combat::attack_declaration::declare_as({ combat::attack_attribute::UNEXPECTED });
    attack_weapon.with(combat::attack_attribute::WITH_MINIMUM);
    declaration.is(combat::attack_attribute::POLARISED);

    CHECK(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::UNEXPECTED));
    CHECK(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::POLARISED));

    declaration.with(attack_weapon);
    declaration.is({ combat::attack_attribute::CONCEDED, combat::attack_attribute::NON_PARRYABLE });

    CHECK_FALSE(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::UNEXPECTED));
    CHECK_FALSE(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::POLARISED));
    CHECK(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::CONCEDED));
    CHECK(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::NON_PARRYABLE));
    CHECK(declaration.attack_status()->weapon.is(combat::attack_attribute::WITH_MINIMUM));
    CHECK_FALSE(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::WITH_MINIMUM));
    CHECK_FALSE(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::COUNTERATTACK));

    declaration.is_not(combat::attack_attribute::CONCEDED);
    CHECK_FALSE(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::CONCEDED));
    CHECK(commons::contains(declaration.attack_status()->attack_attributes, combat::attack_attribute::NON_PARRYABLE));
  }

  SECTION("Should list possible vds, taking into account non-parryable and non-dodgeable attributes")
  {
    auto declaration = combat::attack_declaration::declare_as({ combat::attack_attribute::NON_DODGEABLE, combat::attack_attribute::NON_PARRYABLE }).declared();

    auto vds = declaration.possible_vds();
    CHECK(vds.empty());

    declaration = combat::attack_declaration::declare_as({ combat::attack_attribute::NON_DODGEABLE }).declared();
    vds = declaration.possible_vds();
    CHECK_FALSE(vds.empty());
    CHECK(commons::contains(vds, combat::target_vd::PHYSICAL_PARRY));
    CHECK_FALSE(commons::contains(vds, combat::target_vd::PHYSICAL_DODGE));

    declaration = combat::attack_declaration::declare_as({ combat::attack_attribute::NON_PARRYABLE }).declared();
    vds = declaration.possible_vds();
    CHECK_FALSE(vds.empty());
    CHECK_FALSE(commons::contains(vds, combat::target_vd::PHYSICAL_PARRY));
    CHECK(commons::contains(vds, combat::target_vd::PHYSICAL_DODGE));

    declaration = combat::attack_declaration::declare().declared();
    vds = declaration.possible_vds();
    CHECK_FALSE(vds.empty());
    CHECK(commons::contains(vds, combat::target_vd::PHYSICAL_PARRY));
    CHECK(commons::contains(vds, combat::target_vd::PHYSICAL_DODGE));
  }

  SECTION("Should take into account attack action penalty")
  {
    auto declaration = combat::attack_declaration::declare().with_action_penalty(3);
    REQUIRE(declaration.attack_status()->action_penalty == 3);
  }

  SECTION("Should give a \"fail\" outcome if precision doesn't pass VD")
  {
    auto precision = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 10, 10);
    CHECK(precision.attack_status()->vd == combat::target_vd::PHYSICAL_DODGE);
    auto vd_comparison = precision.with_successes(5);
    REQUIRE_FALSE(vd_comparison.hits());
  }

  SECTION("Should record defender when parrying and dodging")
  {
    auto dodge_precision = combat::attack_declaration::declare().declared()
        .dodge(defense_character, value_calculator);
    REQUIRE(dodge_precision.attack_status()->defender);
    REQUIRE(dodge_precision.attack_status()->vd == combat::target_vd::PHYSICAL_DODGE);
    REQUIRE(dodge_precision.attack_status()->vd_value > 0);
    REQUIRE(dodge_precision.attack_status()->vd_balance > 0);

    auto parry_precision = combat::attack_declaration::declare().declared()
        .parry_with(defense_character, value_calculator, ability::ability_enum::MELEE);
    REQUIRE(parry_precision.attack_status()->defender);
    REQUIRE(parry_precision.attack_status()->vd == combat::target_vd::PHYSICAL_PARRY);
    REQUIRE(parry_precision.attack_status()->vd_value > 0);
    REQUIRE(parry_precision.attack_status()->vd_balance > 0);
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
    CHECK(vd_comparison.hits());

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

  SECTION("Should take into account attribute, ability and specialisation")
  {
    auto vd_comparison = combat::attack_declaration::declare()
        // precision is 7, weapon precision is 5 => 12 dice.
        .attacker(attack_character).with(attack_weapon).declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 10, 10)
        .precision(attack_weapon.precision_attribute(), ability::ability_enum::THROWN)
        .apply(roller);
    REQUIRE(vd_comparison.attack_status()->precision_dice == 12);

    attack_character->add(ability::ability_enum::THROWN, ability::specialisation("Shurikens", 2));
    auto vd_comparison_spec = combat::attack_declaration::declare()
        // precision is 7, weapon precision is 5 => 12 dice.
        .attacker(attack_character).with(attack_weapon).declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 10, 10)
        .precision(attack_weapon.precision_attribute(), ability::ability_enum::THROWN, "Shurikens")
        .apply(roller);
    REQUIRE(vd_comparison_spec.attack_status()->precision_dice == 14);
  }

  SECTION("Should allow counter if parry wins")
  {
    auto vd_comparison_fail = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_PARRY, 10, 10)
        .with_successes(5);
    REQUIRE_FALSE(vd_comparison_fail.hits());
    REQUIRE_FALSE(vd_comparison_fail.on_fail().was_hit());
    REQUIRE(vd_comparison_fail.on_fail().counter_available());
    REQUIRE(vd_comparison_fail.on_fail().final_damage() == 0);
  }

  SECTION("If targeted, the hit should connect in the specified body part")
  {
    roller->set_ratio(1);
    auto when_doesnt_target = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_PARRY, 10, 10)
        .target(combat::body_target::TRUNK)
        .do_not_target();
    CHECK(when_doesnt_target.attack_status()->target == combat::body_target::NO_TARGET);
    CHECK_FALSE(when_doesnt_target.attack_status()->body_part_rolled);

    auto hit_outcome = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_PARRY, 10, 10)
        .target(combat::body_target::TRUNK)
        .with_successes(15).on_success()
        .on_pass(0).on_pass().roll(roller)
        .end_attack();
    REQUIRE(hit_outcome.target_hit() == combat::body_target::TRUNK);
  }

  SECTION("Should compute internal and external bonus when composing precision")
  {
    auto precision = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .bonus(3).malus(5)
        .internal_bonus(4).internal_malus(2).precision(8);
    // 3 - 5 = -2
    CHECK(precision.external_bonus() == -2);
    // 8 + 4 - 2 = 10
    CHECK(precision.pool() == 10);
  }
}
