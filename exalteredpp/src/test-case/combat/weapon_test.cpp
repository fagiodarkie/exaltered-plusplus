#include "../thirdparty/catch/catch.hpp"

#include "equipment/weapon.h"

TEST_CASE("Weapon")
{
  equipment::weapon sut;
  equipment::craft::weapon_project wp;

  SECTION("Should build with fluent APIs correctly")
  {
    wp.with(combat::attack_attribute::WITH_MINIMUM)
        .with_im(3)
        .with_name("axe")
        .with_drill(2)
        .with_range(1.8f)
        .with_defense(1)
        .with_precision(4)
        .uses_for_damage(attribute::attribute_enum::STRENGTH)
        .requires_for_precision(attribute::attribute_enum::DEXTERITY)
        .requires_attribute(attribute::attribute_enum::STRENGTH, 2)
        .with_min_damage(2)
        .with_base_damage(7)
        .with_damage_type(combat::damage_type_enum::LETHAL)
        .use_with(ability::ability_enum::MELEE_LIGHT);

    sut.with_project(wp);
    CHECK(sut.is(combat::attack_attribute::WITH_MINIMUM));
    CHECK(sut.IM() == 3);
    CHECK(sut.name() == "axe");
    CHECK(sut.drill() == 2);
    CHECK(sut.range() - 1.8f < 0.000000001f);
    CHECK(sut.defense() == 1);
    CHECK(sut.precision_bonus() == 4);
    CHECK(sut.damage_attribute() == attribute::attribute_enum::STRENGTH);
    CHECK(sut.precision_attribute() ==attribute::attribute_enum::DEXTERITY);
    CHECK(sut.minimum_for(attribute::attribute_enum::STRENGTH) == 2);
    CHECK(sut.minimum_damage() == 2);
    CHECK(sut.base_damage() == 7);
    CHECK(sut.damage_type() == combat::damage_type_enum::LETHAL);
    CHECK(sut.can_be_used_with(ability::ability_enum::MELEE_LIGHT));
  }

  SECTION("Should add / remove minimum, abilities and combat attributes")
  {
    wp .use_with(ability::ability_enum::MELEE_LIGHT)
        .use_with(ability::ability_enum::THROWN)
        .use_with(ability::ability_enum::ATHLETICS)
        .requires_attribute(attribute::attribute_enum::STRENGTH, 2)
        .requires_attribute(attribute::attribute_enum::DEXTERITY, 2)
        .with(combat::attack_attribute::WITH_MINIMUM)
        .with(combat::attack_attribute::NO_ATTRIBUTE);

    sut.with_project(wp);

    CHECK(sut.can_be_used_with(ability::ability_enum::MELEE_LIGHT));
    CHECK(sut.can_be_used_with(ability::ability_enum::THROWN));
    CHECK(sut.can_be_used_with(ability::ability_enum::ATHLETICS));
    CHECK(sut.requires_minimum_for(attribute::attribute_enum::STRENGTH));
    CHECK(sut.requires_minimum_for(attribute::attribute_enum::DEXTERITY));
    CHECK(sut.is(combat::attack_attribute::WITH_MINIMUM));
    CHECK(sut.is(combat::attack_attribute::NO_ATTRIBUTE));

    wp.does_not_require(attribute::attribute_enum::DEXTERITY)
        .do_not_use_with(ability::ability_enum::ATHLETICS)
        .without(combat::attack_attribute::NO_ATTRIBUTE);

    sut.with_project(wp);

    CHECK(sut.can_be_used_with(ability::ability_enum::MELEE_LIGHT));
    CHECK(sut.can_be_used_with(ability::ability_enum::THROWN));
    CHECK_FALSE(sut.can_be_used_with(ability::ability_enum::ATHLETICS));
    CHECK(sut.requires_minimum_for(attribute::attribute_enum::STRENGTH));
    CHECK_FALSE(sut.requires_minimum_for(attribute::attribute_enum::DEXTERITY));
    CHECK(sut.is(combat::attack_attribute::WITH_MINIMUM));
    CHECK_FALSE(sut.is(combat::attack_attribute::NO_ATTRIBUTE));
  }

}
