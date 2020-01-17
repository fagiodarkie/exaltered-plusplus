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
  (*character)[attribute::STRENGTH] = 2;
  (*character)[attribute::DEXTERITY] = 3;
  (*character)[attribute::CONSTITUTION] = 2;
  (*character)[attribute::CHARISMA] = 2;
  (*character)[attribute::MANIPULATION] = 2;
  (*character)[attribute::APPEARANCE] = 2;
  (*character)[attribute::INTELLIGENCE] = 3;
  (*character)[attribute::WITS] = 2;
  (*character)[ability::MELEE] = 2;
  (*character)[ability::DODGE] = 2;
  (*character)[ability::RESISTANCE] = 3;
  (*character)[ability::INTEGRITY] = 3;
  character->willpower().set_permanent_willpower(5);

  SECTION("should compute values for a mortal")
  {
    character->set_type(character::creation::TYPE_MORTAL_HERO);
    auto phys_defenses = sut.compute_physical_vd(*character, ability::MELEE);
    CHECK(phys_defenses.dodge_vd == 2);
    CHECK(phys_defenses.dodge_balance == 3);
    CHECK(phys_defenses.parry_vd == 2);
    CHECK(phys_defenses.parry_balance == 2);
    CHECK(phys_defenses.tower_parry_vd == 2);
    CHECK(phys_defenses.bashing_soak == 2);
    CHECK(phys_defenses.lethal_soak == 0);
    CHECK(phys_defenses.aggravated_soak == 0);
    auto mental_defenses = sut.compute_mental_vd(*character);
    CHECK(mental_defenses.resilience == 1);
    CHECK(mental_defenses.mental_dodge_vd == 2);
    CHECK(mental_defenses.charisma_parry_vd == 2);
    CHECK(mental_defenses.manipulation_parry_vd == 2);
    CHECK(mental_defenses.appearance_parry_vd == 2);
    auto persona = sut.compute_persona(*character);
    CHECK(persona == 11);
  }

  SECTION("should compute values for an exalt")
  {
    character->set_type(character::creation::TYPE_SOLAR_EXALT);
    character->essence().set_permanent_essence(5);
    character->set(ability::MELEE, 3);
    auto phys_defenses = sut.compute_physical_vd(*character, ability::MELEE);
    CHECK(phys_defenses.dodge_vd == 3);
    CHECK(phys_defenses.parry_vd == 3);
    CHECK(phys_defenses.tower_parry_vd == 3);
    CHECK(phys_defenses.bashing_soak == 2);
    CHECK(phys_defenses.lethal_soak == 1);
    CHECK(phys_defenses.aggravated_soak == 0);
    auto mental_defenses = sut.compute_mental_vd(*character);
    CHECK(mental_defenses.resilience == 2);
    CHECK(mental_defenses.mental_dodge_vd == 3);
    CHECK(mental_defenses.charisma_parry_vd == 3);
    CHECK(mental_defenses.manipulation_parry_vd == 3);
    CHECK(mental_defenses.appearance_parry_vd == 3);
    auto persona = sut.compute_persona(*character);
    CHECK(persona == 14 );
  }
}
