#include "../thirdparty/catch/catch.hpp"

#include <memory>
#include "calculator/derived_value_calculator.h"
#include "calculator/worker/common_worker.h"
#include "calculator/worker/exalt_worker.h"

TEST_CASE("Derived Value Calculator")
{
  calculator::derived_value_calculator sut({
                                             { character::creation::TYPE_MORTAL_HERO, std::make_shared<calculator::worker::human_worker>() },
                                             { character::creation::TYPE_SOLAR_EXALT, std::make_shared<calculator::worker::exalt_worker>() }
                                           });

  auto character = std::make_shared<character::character>("");
  (*character)[attribute::attribute_enum::STRENGTH] = 2;
  (*character)[attribute::attribute_enum::DEXTERITY] = 3;
  (*character)[attribute::attribute_enum::CONSTITUTION] = 2;
  (*character)[attribute::attribute_enum::CHARISMA] = 2;
  (*character)[attribute::attribute_enum::MANIPULATION] = 2;
  (*character)[attribute::attribute_enum::APPEARANCE] = 2;
  (*character)[attribute::attribute_enum::INTELLIGENCE] = 3;
  (*character)[attribute::attribute_enum::WITS] = 2;
  (*character)[ability::ability_enum::MELEE_LIGHT] = 2;
  (*character)[ability::ability_enum::DODGE] = 2;
  (*character)[ability::ability_enum::RESISTANCE] = 3;
  (*character)[ability::ability_enum::INTEGRITY] = 3;
  (*character)[ability::ability_enum::MEDITATION] = 3;
  character->virtue(virtues::COMPASSION).set_value(2);
  character->virtue(virtues::VALOR).set_value(2);
  character->virtue(virtues::CONVINCTION).set_value(3);
  character->virtue(virtues::TEMPERANCE).set_value(3);
  character->willpower().set_permanent_willpower(5);
  character->essence().set_permanent_essence(1);
  character->logos().set_logos(1);
  character->rest();

  SECTION("should compute values for a mortal")
  {
    character->set_type(character::creation::TYPE_MORTAL_HERO);
    auto phys_defenses = sut.compute_physical_vd(*character, ability::ability_enum::MELEE_LIGHT);
    auto soaks = sut.compute_soak_values(*character);
    CHECK(phys_defenses.dodge_vd == 2);
    CHECK(phys_defenses.dodge_balance == 3);
    CHECK(phys_defenses.parry_vd == 2);
    CHECK(phys_defenses.parry_balance == 2);
    CHECK(phys_defenses.tower_parry_vd == 2);
    CHECK(soaks.natural_soak[combat::damage_type_enum::BASHING]     == 2);
    CHECK(soaks.natural_soak[combat::damage_type_enum::LETHAL]      == 0);
    CHECK(soaks.natural_soak[combat::damage_type_enum::AGGRAVATED]  == 0);
    auto mental_defenses = sut.compute_mental_vd(*character);
    CHECK(mental_defenses.mental_dodge_vd == 2);
    CHECK(mental_defenses.charisma_parry_vd == 2);
    CHECK(mental_defenses.manipulation_parry_vd == 2);
    CHECK(mental_defenses.appearance_parry_vd == 2);
    auto persona = sut.compute_persona(*character);
    CHECK(persona == 7);
    CHECK(sut.compute_persona(character->type(), character->attributes(), character->logos(), character->essence()) == 7);
    CHECK(sut.compute_life_points(*character) == 14);
    CHECK_NOTHROW(sut.compute_personal_essence(*character));
    CHECK_NOTHROW(sut.compute_peripheral_essence(*character));
    CHECK_NOTHROW(sut.compute_spiritual_essence(*character));
    CHECK_NOTHROW(sut.compute_celestial_portion(*character));
    CHECK(sut.starting_khan(character->type()) == 0);
    CHECK(sut.starting_essence(character->type()) == 1);
    CHECK(sut.starting_logos(character->type()) == 1);
    CHECK(sut.starting_willpower(*character) == 6);
  }

  SECTION("should compute values for an exalt")
  {
    character->set_type(character::creation::TYPE_SOLAR_EXALT);
    character->essence().set_permanent_essence(5);
    character->logos().set_logos(2);
    character->set(ability::ability_enum::MELEE_LIGHT, 3);
    auto phys_defenses = sut.compute_physical_vd(*character, ability::ability_enum::MELEE_LIGHT);
    auto soaks = sut.compute_soak_values(*character);
    CHECK(phys_defenses.dodge_vd == 3);
    CHECK(phys_defenses.parry_vd == 3);
    CHECK(phys_defenses.tower_parry_vd == 3);
    CHECK(soaks.natural_soak[combat::damage_type_enum::BASHING]      == 2);
    CHECK(soaks.natural_soak[combat::damage_type_enum::LETHAL]       == 1);
    CHECK(soaks.natural_soak[combat::damage_type_enum::AGGRAVATED]   == 0);
    auto mental_defenses = sut.compute_mental_vd(*character);
    CHECK(mental_defenses.mental_dodge_vd == 3);
    CHECK(mental_defenses.charisma_parry_vd == 3);
    CHECK(mental_defenses.manipulation_parry_vd == 3);
    CHECK(mental_defenses.appearance_parry_vd == 3);
    auto persona = sut.compute_persona(*character);
    CHECK(persona == 16 );
  }
}
