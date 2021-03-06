#include "../thirdparty/catch/catch.hpp"

#include "abilities/ability_group.h"

TEST_CASE("Ability group")
{

  SECTION("should create simple ability by default")
  {
    ability::ability_group sut;
    REQUIRE(sut.has(ability::ability_declination::NO_DECLINATION));
    REQUIRE_FALSE(sut.has_abilities());
  }

  SECTION("if created with default declination, should be seen as simple")
  {
    ability::ability_group sut(ability::WAR, {ability::ability(ability::ability_declination::NO_DECLINATION)});
    REQUIRE(sut.has(ability::ability_declination::NO_DECLINATION));
    REQUIRE_FALSE(sut.has_abilities());
  }

  SECTION("should consider ability declinations and specialisations if requested")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE_FALSE(sut.has(ability::ability_declination::NO_DECLINATION));
    REQUIRE(sut.has_abilities());

    REQUIRE_THROWS(sut.get());
  }

  SECTION("should keep right values of abilities")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE(sut.get("a1").value() == 1);
    REQUIRE(sut.get("a2").value() == 2);
  }

  SECTION("should change ability names if it has ability declinations")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE(sut.get_abilities().at(0).name() == "War (a1)");
    REQUIRE(sut.get_abilities().at(1).name() == "War (a2)");
  }

  SECTION("should not change ability names if it is simple")
  {
    ability::ability_group sut;
    REQUIRE(sut.get_abilities().at(0).name() == "War");
  }

  SECTION("should not prevent new ability if it has ability declinations")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE_NOTHROW(sut.add_ability("a3"));
    REQUIRE(sut.get("a3").name() == "a3");
  }

  SECTION("should prevent new ability if it is simple")
  {
    ability::ability_group sut;
    REQUIRE_THROWS(sut.add_ability("a1"));
    REQUIRE_FALSE(sut.has("a1"));
    REQUIRE_THROWS(sut.get("a1"));
  }

  SECTION("should not change specialisation names")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    ability::ability_group sut_simple;
    sut_simple.add_specialisation(ability::specialisation("s1"));
    REQUIRE(sut.get_specialisations().at(0).name() == "s1");
    REQUIRE(sut_simple.get_specialisations().at(0).name() == "s1");
  }

  SECTION("should throw if specialisation doesn't exist")
  {
    ability::ability_group sut;
    REQUIRE_FALSE(sut.has_specialisation("doesn't exist"));
    REQUIRE_THROWS(sut.get_specialisation("doesn't exist"));
  }

  SECTION("should keep specialisation value")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE(sut.get_specialisations().size() == 1);
    REQUIRE(sut.has_specialisation("s1"));
    REQUIRE(sut.get_specialisation("s1").name() == "s1");
    REQUIRE(sut.get_specialisation("s1").value() == 3);
  }

  SECTION("should allow new ability and specialisation generation with name / value pairs")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    sut.add_ability("a3", 1);
    sut.add_specialisation("s2", 2);
    REQUIRE(sut.has("a3"));
    REQUIRE(sut.has_specialisation("s2"));
  }

  SECTION("should allow to modify ability values")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    sut.set("a1", 0);
    REQUIRE(sut.get("a1") == 0);
    sut.increase_ability_value("a1");
    REQUIRE(sut.get("a1") == 1);
    sut.increase_ability_value("a1", 2);
    REQUIRE(sut.get("a1") == 3);
    sut.add_ability(ability::ability("a1", 4));
    REQUIRE(sut.get("a1") == 4);
    sut.add_ability(ability::ability("a3", 4));
    REQUIRE(sut.get("a3") == 4);
  }

  SECTION("should not throw if trying to update a non-existing ability")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE_NOTHROW(sut.set("a3", 4));
  }

  SECTION("should allow to modify specialisation values")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    sut.set_specialisation_value("s1", 0);
    REQUIRE(sut.get_specialisation("s1").value() == 0);
    sut.increase_specialisation_value("s1");
    REQUIRE(sut.get_specialisation("s1").value() == 1);
    sut.increase_specialisation_value("s1", 2);
    REQUIRE(sut.get_specialisation("s1").value() == 3);
  }

  SECTION("should allow to remove specialisation")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE_NOTHROW(sut.remove_specialisation("s2"));
    REQUIRE(sut.get_specialisations().size() == 1);
    REQUIRE_NOTHROW(sut.remove_specialisation("s1"));
    REQUIRE(sut.get_specialisations().size() == 0);
  }

  SECTION("should save category")
  {
    ability::ability_group sut;
    REQUIRE(sut.get_category() == ability::COMBAT);
  }

  SECTION("should save favorite flag")
  {
    ability::ability_group sut;
    REQUIRE_FALSE(sut.get().favored());
    sut.set_favored(true);
    REQUIRE(sut.get().favored());
    sut.set_favored(false);
    REQUIRE_FALSE(sut.get().favored());
  }

  SECTION("should save and load successfully with JSON Object")
  {
    ability::ability_group stub(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});

    ability::ability_group sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut.get_name()                            == stub.get_name()                           );
    REQUIRE(sut.get_category()                        == stub.get_category()                       );
    REQUIRE(sut.get("a1").favored()      == stub.get("a1").favored()     );
    REQUIRE(sut.get("a1").value() == stub.get("a1").value());
    REQUIRE(sut.get("a2").value() == stub.get("a2").value());
  }

  SECTION("should copy successfully withcopy constructor and assignment operator")
  {
    ability::ability_group stub(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});

    ability::ability_group sut_1(stub), sut_2;
    sut_2 = stub;

    REQUIRE(sut_1.get_name()                            == stub.get_name()                           );
    REQUIRE(sut_1.get_category()                        == stub.get_category()                       );
    REQUIRE(sut_1.get("a1").favored()      == stub.get("a1").favored()     );
    REQUIRE(sut_1.get("a1").value() == stub.get("a1").value());
    REQUIRE(sut_1.get("a2").value() == stub.get("a2").value());

    REQUIRE(sut_2.get_name()                            == stub.get_name()                           );
    REQUIRE(sut_2.get_category()                        == stub.get_category()                       );
    REQUIRE(sut_2.get("a1").favored()      == stub.get("a1").favored()     );
    REQUIRE(sut_2.get("a1").value() == stub.get("a1").value());
    REQUIRE(sut_2.get("a2").value() == stub.get("a2").value());
  }

  SECTION("should not throw if asked to retrieve unknown abilities or specialisation")
  {
    ability::ability_group stub(ability::WAR);

    REQUIRE_NOTHROW(stub.set("invalid_ability", 4));
    REQUIRE_NOTHROW(stub.set_specialisation_value("invalid_specialisation", 2));
  }

  SECTION("should retrieve the ability type")
  {
    ability::ability_group sut(ability::WAR);
    REQUIRE(sut.get_enum() == ability::WAR);
  }

  SECTION("should list subabilities")
  {
    ability::ability_group sut(ability::WAR, {ability::ability("a1"), ability::ability("a2")});
    auto result = sut.get_detailed_abilities();
    REQUIRE(result.size() == 2);
    REQUIRE(result[0].name() == "War (a1)");
    REQUIRE(result[1].name() == "War (a2)");
  }
}
