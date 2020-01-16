#include "../thirdparty/catch/catch.hpp"
#include "worker/exalt_worker.h"
#include "qt-test/quick_chargen.h"

using calculator::worker::human_worker;
using calculator::worker::exalt_worker;

TEST_CASE("common worker")
{
  human_worker sut;
  character::character test_character = generate_character("name", 0);
  test_character.set(attribute::DEXTERITY, 4);
  test_character.set(attribute::STRENGTH, 3);
  test_character.set(attribute::CONSTITUTION, 3);
  test_character.set(attribute::INTELLIGENCE, 3);
  test_character.set(attribute::CHARISMA, 3);
  test_character.set(attribute::MANIPULATION, 3);
  test_character.set(attribute::APPEARANCE, 3);
  test_character.set(attribute::WITS, 3);
  test_character.set(ability::MELEE, 3);
  test_character.set(ability::DODGE, 3);
  test_character.set(ability::RESISTANCE, 3);
  test_character.set(ability::INTEGRITY, 3);

  SECTION("should compute human values rounding down")
  {
    // parry is ((dex + str) / 2 + ability) / 2. In this case it's ((4 + 3) / 2 + 3) / 2, which should yield 3 instead of 4 since it rounds down
    REQUIRE(sut.compute_parry_dv(test_character, ability::MELEE) == 3);
    // same for dodge, (4 + 3) / 2 = 3
    REQUIRE(sut.compute_dodge_dv(test_character) == 3);
  }

  SECTION("all values must be implemented")
  {
    REQUIRE_NOTHROW(sut.compute_dodge_dv               (test_character));
    REQUIRE_NOTHROW(sut.compute_parry_dv               (test_character, ability::MELEE));
    REQUIRE_NOTHROW(sut.compute_heavy_parry_dv         (test_character, ability::MELEE));
    REQUIRE_NOTHROW(sut.compute_mental_dodge_dv        (test_character));
    REQUIRE_NOTHROW(sut.compute_mental_parry_dv        (test_character, attribute::CHARISMA));
    REQUIRE_NOTHROW(sut.compute_persona                (test_character));
    REQUIRE_NOTHROW(sut.compute_bashing_soak           (test_character));
    REQUIRE_NOTHROW(sut.compute_lethal_soak            (test_character));
    REQUIRE_NOTHROW(sut.compute_aggravated_soak        (test_character));
    REQUIRE_NOTHROW(sut.compute_natural_bashing_soak   (test_character));
    REQUIRE_NOTHROW(sut.compute_natural_lethal_soak    (test_character));
    REQUIRE_NOTHROW(sut.compute_natural_aggravated_soak(test_character));
    REQUIRE_NOTHROW(sut.compute_personal_essence       (test_character));
    REQUIRE_NOTHROW(sut.compute_peripheral_essence     (test_character));
    REQUIRE_NOTHROW(sut.compute_spiritual_essence      (test_character));
    REQUIRE_NOTHROW(sut.compute_celestial_portion      (test_character));
    REQUIRE_NOTHROW(sut.compute_life_points            (test_character));
    REQUIRE_NOTHROW(sut.starting_willpower             (test_character));
    REQUIRE_NOTHROW(sut.compute_parry_balance          (test_character));
    REQUIRE_NOTHROW(sut.compute_dodge_balance          (test_character));
    REQUIRE_NOTHROW(sut.compute_stance_bonus           (test_character));
    REQUIRE_NOTHROW(sut.compute_hindrance              (test_character));

    REQUIRE_NOTHROW(sut.starting_logos                 (test_character.type()));
    REQUIRE_NOTHROW(sut.starting_khan                  (test_character.type()));
    REQUIRE_NOTHROW(sut.starting_essence               (test_character.type()));
  }
}

TEST_CASE("exalt worker")
{
  exalt_worker sut;
  character::character test_character = generate_character("name", 0);

  SECTION("should compute human values rounding up")
  {
    test_character.set(attribute::DEXTERITY, 4);
    test_character.set(attribute::STRENGTH, 3);
    test_character.set(attribute::MANIPULATION, 5);
    test_character.set(attribute::CHARISMA, 5);
    test_character.set(attribute::APPEARANCE, 1);
    test_character.willpower().set_permanent_willpower(5);
    test_character.essence().set_permanent_essence(5);
    test_character.set(ability::MELEE, 3);
    test_character.set(ability::DODGE, 3);

    // parry is ((dex + str) / 2 + ability) / 2. In this case it's ((4 + 3) / 2 + 3) / 2, which should yield 4 since it rounds up
    REQUIRE(sut.compute_parry_dv(test_character, ability::MELEE) == 4);
    // same for dodge, (4 + 3) / 2 = 4
    REQUIRE(sut.compute_dodge_dv(test_character) == 4);

    // persona should be 20 as essence is 5 and willpower is 5, even if APPEARANCE is 1
    REQUIRE(sut.compute_persona(test_character.type(), test_character.attributes(), test_character.willpower(), test_character.essence()) == 20);
  }

}
