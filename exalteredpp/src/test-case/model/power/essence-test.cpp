#include "../thirdparty/catch/catch.hpp"
#include "power/essence.h"

TEST_CASE("essence")
{
  SECTION("should create essence with default values")
  {
    power::essence sut;
    REQUIRE(sut.permanent_essence() == 1);
    REQUIRE(sut.khan() == 1);
  }

  SECTION("should create essence from JSON object")
  {
    power::essence stub;

    stub.set_permanent_essence(2);
    stub.set_khan(3);
    stub.set_celestial_portion(60);
    stub.set_total_personal_essence(100);
    stub.set_total_peripheral_essence(200);
    stub.set_total_spiritual_essence(300);
    stub.spend_essence(10);
    stub.spend_spiritual_essence(20);
    stub.commit_essence(30);
    stub.commit_spiritual_essence(40);
    stub.set_bonus_personal_essence(50);
    stub.set_bonus_peripheral_essence(60);
    stub.set_bonus_spiritual_essence(70);

    power::essence sut;
    sut.deserialise(stub.serialise());

    REQUIRE(stub.permanent_essence()                == sut.permanent_essence()               );
    REQUIRE(stub.khan()                             == sut.khan()                            );
    REQUIRE(stub.total_personal_essence()           == sut.total_personal_essence()          );
    REQUIRE(stub.total_peripheral_essence()         == sut.total_peripheral_essence()        );
    REQUIRE(stub.total_spiritual_essence()          == sut.total_spiritual_essence()         );
    REQUIRE(stub.get_celestial_portion_percentage() == sut.get_celestial_portion_percentage());
    REQUIRE(stub.available_personal_essence()       == sut.available_personal_essence()      );
    REQUIRE(stub.available_peripheral_essence()     == sut.available_peripheral_essence()    );
    REQUIRE(stub.available_spiritual_essence()      == sut.available_spiritual_essence()     );
  }

  SECTION("should not allow to spend more essence than the total")
  {
    power::essence sut;
    sut.set_total_personal_essence(10);
    sut.set_total_peripheral_essence(10);
    sut.set_total_spiritual_essence(10);
    sut.set_bonus_personal_essence(10);
    sut.set_bonus_peripheral_essence(10);
    sut.set_bonus_spiritual_essence(10);

    CHECK(sut.can_spend_essence(20));
    CHECK(sut.can_spend_spiritual_essence(10));
    CHECK_FALSE(sut.can_spend_essence(50));
    CHECK_FALSE(sut.can_spend_spiritual_essence(30));

    sut.spend_essence(20);
    sut.spend_spiritual_essence(10);

    CHECK(sut.can_spend_essence(20));
    CHECK(sut.can_spend_spiritual_essence(10));
    CHECK_FALSE(sut.can_spend_essence(30));
    CHECK_FALSE(sut.can_spend_spiritual_essence(20));

    sut.spend_essence(15);
    sut.spend_spiritual_essence(8);

    CHECK(sut.can_spend_essence(5));
    CHECK(sut.can_spend_spiritual_essence(2));
    CHECK_FALSE(sut.can_spend_essence(10));
    CHECK_FALSE(sut.can_spend_spiritual_essence(10));
  }

  SECTION("should use and recover essence from the personal pool before touching the peripheral pool")
  {
    power::essence sut;
    sut.set_total_personal_essence(10);
    sut.set_total_peripheral_essence(10);
    sut.set_total_spiritual_essence(10);

    sut.spend_essence(5);
    CHECK(sut.available_personal_essence() == 5);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.spend_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 5);

    sut.spend_essence(5);
    CHECK(sut.available_personal_essence() == 0);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.spend_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 0);

    sut.spend_essence(5);
    CHECK(sut.available_personal_essence() == 0);
    CHECK(sut.available_peripheral_essence() == 5);
    sut.spend_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 0);

    sut.recover_essence(10);
    CHECK(sut.available_personal_essence() == 5);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.recover_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 5);

    sut.recover_essence(5);
    CHECK(sut.available_personal_essence() == 10);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.recover_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 10);

    sut.recover_essence(5);
    CHECK(sut.available_personal_essence() == 10);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.recover_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 10);
  }

  SECTION("committed essence should count as spent")
  {
    power::essence sut;
    sut.set_total_personal_essence(10);
    sut.set_total_peripheral_essence(10);
    sut.set_total_spiritual_essence(10);

    sut.commit_essence(5);
    CHECK(sut.available_personal_essence() == 5);
    CHECK(sut.committed_personal_essence() == 5);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.commit_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 5);

    sut.commit_essence(5);
    CHECK(sut.available_personal_essence() == 0);
    CHECK(sut.committed_personal_essence() == 10);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.commit_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 0);

    sut.commit_essence(5);
    CHECK(sut.available_personal_essence() == 0);
    CHECK(sut.committed_peripheral_essence() == 5);
    CHECK(sut.available_peripheral_essence() == 5);
    sut.commit_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 0);

    sut.decommit_essence(10);
    CHECK(sut.available_personal_essence() == 5);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.decommit_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 5);

    sut.decommit_essence(5);
    CHECK(sut.available_personal_essence() == 10);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.decommit_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 10);

    sut.decommit_essence(5);
    CHECK(sut.available_personal_essence() == 10);
    CHECK(sut.available_peripheral_essence() == 10);
    sut.decommit_spiritual_essence(5);
    CHECK(sut.available_spiritual_essence() == 10);
  }

  SECTION("should get and set essence and khan consistently")
  {
    power::essence sut;

    sut.set_khan(2);
    sut.set_permanent_essence(4);

    REQUIRE(sut.khan() == 2);
    REQUIRE(sut.permanent_essence() == 4);
  }

  SECTION("should compute portion percentages consistently")
  {
    power::essence sut;
    sut.set_celestial_portion(60);
    REQUIRE(sut.get_celestial_portion_percentage() == 60);
    REQUIRE(sut.get_terrestrial_portion_percentage() == 40);

    sut.set_celestial_portion(10);
    REQUIRE(sut.get_celestial_portion_percentage() == 10);
    REQUIRE(sut.get_terrestrial_portion_percentage() == 90);
  }
}
