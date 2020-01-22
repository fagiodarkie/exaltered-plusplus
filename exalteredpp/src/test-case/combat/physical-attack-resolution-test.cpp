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
    roller->set_ratio(0.3f);
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
    auto vd_comparison_fail = combat::attack_declaration::declare()
        .with_action_penalty(3).declared()
        .defend_with_value(combat::target_vd::PHYSICAL_PARRY, 10, 10)
        .with_successes(5);
    REQUIRE_FALSE(vd_comparison_fail.hits());
    REQUIRE_FALSE(vd_comparison_fail.on_fail().was_hit());
    REQUIRE(vd_comparison_fail.on_fail().counter_available());
    REQUIRE(vd_comparison_fail.on_fail().vd_penalty_on_attacker() == 3);
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

  SECTION("Should recompute VD when adding VD bonus or malus")
  {
    auto vd_computation = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .with_successes(5);
    CHECK(vd_computation.hits());
    vd_computation.bonus(4);
    CHECK_FALSE(vd_computation.hits());
    vd_computation.malus(3);
    CHECK(vd_computation.hits());
  }

  SECTION("Should compute damage attribute if the attacker was not given")
  {
    auto damage_computation = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .with_successes(5)
        .on_success();
    // 3 extra successes
    damage_computation.base_damage(5)
      .attribute(4)
      .damage_type(combat::damage_type_enum::BASHING)
      .drill(5);
    // total: 12 die / 5 drill
    CHECK(damage_computation.attack_status()->raw_damage() == 12);
    CHECK(damage_computation.passes(10));
    CHECK(damage_computation.attack_status()->post_soak_damage == 2);
    CHECK_FALSE(damage_computation.passes(12));
    CHECK(damage_computation.attack_status()->post_soak_damage == 0);

    CHECK(damage_computation.passes(8, 4));
    CHECK(damage_computation.attack_status()->post_soak_damage == 4);
    CHECK_FALSE(damage_computation.passes(10, 8));
    CHECK(damage_computation.attack_status()->post_soak_damage == 0);
  }

  SECTION("Should compute damage attribute if the attacker was given")
  {
    auto damage_computation = combat::attack_declaration::declare()
        .with(attack_weapon)
        .attacker(attack_character)
        .declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .with_successes(5)
        .on_success()
        // try to set weapon properties - they should be ignored
        .base_damage(100)
        .attribute(100)
        .min_damage(100)
        .damage_type(combat::damage_type_enum::SPIRITUAL)
        .drill(100);
    CHECK_FALSE(damage_computation.attack_status()->weapon.drill() == 100);
    CHECK_FALSE(damage_computation.attack_status()->damage_attribute == 100);
    CHECK_FALSE(damage_computation.attack_status()->weapon.damage_type() == combat::damage_type_enum::SPIRITUAL);
    CHECK_FALSE(damage_computation.attack_status()->weapon.base_damage() == 100);
    CHECK_FALSE(damage_computation.attack_status()->weapon.minimum_damage() == 100);
    // 3 extra successes, str 3, base damage 3: 9 raw damage dice
    CHECK(damage_computation.attack_status()->raw_damage() == 9);
    CHECK_FALSE(damage_computation.passes(10));
  }


  SECTION("Should impose minimum damage if the soak completely blocks the attack")
  {
    auto damage_computation = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .with_successes(5)
        .on_success();
    // 3 extra successes
    damage_computation.base_damage(5);
    damage_computation.attribute(4);
    CHECK_FALSE(damage_computation.passes(16));
    auto failure = damage_computation.on_fail();
    CHECK(failure.was_hit());
    CHECK(failure.final_damage() == 0);
    damage_computation.min_damage(6);
    CHECK(damage_computation.passes(16));
    CHECK(damage_computation.attack_status()->is_damage_from_minimum);
  }

  SECTION("Should compute body target if it wasn't specified already")
  {
    auto damage_computation = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .with_successes(5)
        .on_success();
    CHECK(damage_computation.attack_status()->target == combat::body_target::NO_TARGET);
    CHECK_FALSE(damage_computation.target() == combat::body_target::NO_TARGET);
    CHECK_FALSE(damage_computation.attack_status()->target == combat::body_target::NO_TARGET);
  }

  SECTION("Should not pass on hardness check if raw is low and there is no minimum damage")
  {
    auto min_damage_computation = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .with_successes(5)
        .on_success()
        .min_damage(10)
        // passes with minimum damage
        .on_pass(15);
    CHECK(min_damage_computation.passes(0));
    CHECK(min_damage_computation.passes(5));
    CHECK(min_damage_computation.passes(15));

    auto damage_computation = combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .with_successes(5)
        // 3 extra successes
        .on_success()
        .attribute(3)
        .base_damage(4)
        // passes with full regular damage (10 dice)
        .on_pass(0);
    CHECK(damage_computation.passes(0));
    CHECK(damage_computation.passes(5));
    CHECK_FALSE(damage_computation.passes(15));
  }

  SECTION("Should take defender's soak if defender is specified")
  {
    auto damage_computation = combat::attack_declaration::declare().declared()
        .dodge(defense_character, value_calculator)
        .with_successes(8)
        .on_success().damage_type(combat::damage_type_enum::BASHING);
    // 4 extra successes, defender CON = 2 --> 2 bashing soak as he's mortal
    CHECK(damage_computation.passes(value_calculator));
    CHECK(damage_computation.on_pass(value_calculator).attack_status()->post_soak_damage == 2);
  }

  SECTION("Final damage should take into account knockdown and knockback")
  {
    auto create_damage = []() {
        return combat::attack_declaration::declare().declared()
        .defend_with_value(combat::target_vd::PHYSICAL_DODGE, 2, 2)
        .with_successes(5)
        .on_success()
        .min_damage(10)
        .on_pass(15).on_pass().with_roll(10);
      };
    auto knockdown_fail = create_damage().knockdown(2).end_attack();
    CHECK_FALSE(knockdown_fail.was_knocked_down());
    CHECK_FALSE(knockdown_fail.was_pushed());
    CHECK(knockdown_fail.final_damage() == 8);

    auto knockdown_hit = create_damage().knockdown(5).end_attack();
    CHECK(knockdown_hit.was_knocked_down());
    CHECK_FALSE(knockdown_hit.was_pushed());
    CHECK(knockdown_hit.final_damage() == 5);

    auto knockback_fail = create_damage().knockback_meters(2).end_attack();
    CHECK_FALSE(knockback_fail.was_knocked_down());
    CHECK_FALSE(knockback_fail.was_pushed());
    CHECK(knockback_fail.final_damage() == 8);

    auto knockback_hit = create_damage().knockback_meters(8).end_attack();
    CHECK_FALSE(knockback_hit.was_knocked_down());
    CHECK(knockback_hit.was_pushed());
    CHECK(knockback_hit.meters_pushed() == 6);
    CHECK(knockback_hit.final_damage() == 2);
  }
}
