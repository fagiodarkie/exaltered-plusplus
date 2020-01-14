#include "../thirdparty/catch/catch.hpp"

#include "abilities/ability_group.h"

TEST_CASE("Ability group")
{

  SECTION("should create simple ability by default")
  {
    ability::ability_group sut;
    REQUIRE(sut.has_ability(ability::ability_declination::NO_DECLINATION));
    REQUIRE_FALSE(sut.has_abilities());
  }

  SECTION("if created with default declination, should be seen as simple")
  {
    ability::ability_group sut(ability::WAR, {ability::ability(ability::ability_declination::NO_DECLINATION)});
    REQUIRE(sut.has_ability(ability::ability_declination::NO_DECLINATION));
    REQUIRE_FALSE(sut.has_abilities());
  }

  SECTION("should consider ability declinations and specialisations if requested")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE_FALSE(sut.has_ability(ability::ability_declination::NO_DECLINATION));
    REQUIRE(sut.has_abilities());

    REQUIRE_THROWS(sut.get_ability());
  }

  SECTION("should keep right values of abilities")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE(sut.get_ability("a1").get_ability_value() == 1);
    REQUIRE(sut.get_ability("a1").get_value() == "1");
    REQUIRE(sut.get_ability("a2").get_ability_value() == 2);
    REQUIRE(sut.get_ability("a2").get_value() == "2");
  }

  SECTION("should change ability names if it has ability declinations")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE(sut.get_abilities().at(0).get_name() == "War (a1)");
    REQUIRE(sut.get_abilities().at(1).get_name() == "War (a2)");
  }

  SECTION("should not change ability names if it is simple")
  {
    ability::ability_group sut;
    REQUIRE(sut.get_abilities().at(0).get_name() == "War");
  }

  SECTION("should not prevent new ability if it has ability declinations")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE_NOTHROW(sut.add_ability("a3"));
    REQUIRE(sut.get_ability("a3").get_name() == "a3");
  }

  SECTION("should prevent new ability if it is simple")
  {
    ability::ability_group sut;
    REQUIRE_THROWS(sut.add_ability("a1"));
    REQUIRE_FALSE(sut.has_ability("a1"));
    REQUIRE_THROWS(sut.get_ability("a1"));
  }

  SECTION("should not change specialisation names")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    ability::ability_group sut_simple;
    sut_simple.add_specialisation(ability::specialisation("s1"));
    REQUIRE(sut.get_specialisations().at(0).get_name() == "s1");
    REQUIRE(sut_simple.get_specialisations().at(0).get_name() == "s1");
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
    REQUIRE(sut.get_specialisation("s1").get_value() == "3");
    REQUIRE(sut.get_specialisation("s1").get_name() == "s1");
    REQUIRE(sut.get_specialisation("s1").get_specialisation_value() == 3);
  }

  SECTION("should allow new ability and specialisation generation with name / value pairs")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    sut.add_ability("a3", 1);
    sut.add_specialisation("s2", 2);
    REQUIRE(sut.has_ability("a3"));
    REQUIRE(sut.has_specialisation("s2"));
  }

  SECTION("should allow to modify ability values")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    sut.set_ability_value("a1", 0);
    REQUIRE(sut.get_ability("a1") == 0);
    sut.increase_ability_value("a1");
    REQUIRE(sut.get_ability("a1") == 1);
    sut.increase_ability_value("a1", 2);
    REQUIRE(sut.get_ability("a1") == 3);
    sut.add_ability(ability::ability("a1", 4));
    REQUIRE(sut.get_ability("a1") == 4);
    sut.add_ability(ability::ability("a3", 4));
    REQUIRE(sut.get_ability("a3") == 4);
  }

  SECTION("should throw if trying to update a non-existing ability")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    REQUIRE_THROWS(sut.set_ability_value("a3", 4));
  }

  SECTION("should allow to modify specialisation values")
  {
    ability::ability_group sut(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});
    sut.set_specialisation_value("s1", 0);
    REQUIRE(sut.get_specialisation("s1").get_specialisation_value() == 0);
    sut.increase_specialisation_value("s1");
    REQUIRE(sut.get_specialisation("s1").get_specialisation_value() == 1);
    sut.increase_specialisation_value("s1", 2);
    REQUIRE(sut.get_specialisation("s1").get_specialisation_value() == 3);
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
    REQUIRE_FALSE(sut.get_ability().is_favourite());
    sut.set_favourite(true);
    REQUIRE(sut.get_ability().is_favourite());
    sut.set_favourite(false);
    REQUIRE_FALSE(sut.get_ability().is_favourite());
  }

  SECTION("should save and load successfully with JSON Object")
  {
    ability::ability_group stub(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});

    ability::ability_group sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut.get_name()                            == stub.get_name()                           );
    REQUIRE(sut.get_category()                        == stub.get_category()                       );
    REQUIRE(sut.get_ability("a1").is_favourite()      == stub.get_ability("a1").is_favourite()     );
    REQUIRE(sut.get_ability("a1").get_ability_value() == stub.get_ability("a1").get_ability_value());
    REQUIRE(sut.get_ability("a2").get_ability_value() == stub.get_ability("a2").get_ability_value());
    REQUIRE(sut.get_specialisation("s1").get_value()  == stub.get_specialisation("s1").get_value() );
  }

  SECTION("should copy successfully withcopy constructor and assignment operator")
  {
    ability::ability_group stub(ability::WAR, { ability::ability("a1", 1), ability::ability("a2", 2) }, {ability::specialisation("s1", 3)});

    ability::ability_group sut_1(stub), sut_2;
    sut_2 = stub;

    REQUIRE(sut_1.get_name()                            == stub.get_name()                           );
    REQUIRE(sut_1.get_category()                        == stub.get_category()                       );
    REQUIRE(sut_1.get_ability("a1").is_favourite()      == stub.get_ability("a1").is_favourite()     );
    REQUIRE(sut_1.get_ability("a1").get_ability_value() == stub.get_ability("a1").get_ability_value());
    REQUIRE(sut_1.get_ability("a2").get_ability_value() == stub.get_ability("a2").get_ability_value());
    REQUIRE(sut_1.get_specialisation("s1").get_value()  == stub.get_specialisation("s1").get_value() );

    REQUIRE(sut_2.get_name()                            == stub.get_name()                           );
    REQUIRE(sut_2.get_category()                        == stub.get_category()                       );
    REQUIRE(sut_2.get_ability("a1").is_favourite()      == stub.get_ability("a1").is_favourite()     );
    REQUIRE(sut_2.get_ability("a1").get_ability_value() == stub.get_ability("a1").get_ability_value());
    REQUIRE(sut_2.get_ability("a2").get_ability_value() == stub.get_ability("a2").get_ability_value());
    REQUIRE(sut_2.get_specialisation("s1").get_value()  == stub.get_specialisation("s1").get_value() );
  }

  SECTION("should throw if asked to retrieve invalid abilities or specialisation")
  {
    ability::ability_group stub(ability::WAR);

    REQUIRE_THROWS(stub.set_ability_value("invalid_ability", 4));
    REQUIRE_THROWS(stub.set_specialisation_value("invalid_specialisation", 2));
  }
}
