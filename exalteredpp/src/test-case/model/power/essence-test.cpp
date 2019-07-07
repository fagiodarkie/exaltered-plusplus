#include "../thirdparty/catch/catch.hpp"
#include "power/essence.h"

TEST_CASE("essence")
{
  SECTION("should create essence with default values")
  {
    character::power::essence sut;
    REQUIRE(sut.permanent_essence() == 1);
    REQUIRE(sut.khan() == 1);
  }

  SECTION("should create essence from JSON object")
  {
    character::power::essence stub;

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

    QJsonObject obj;
    stub.write_to_json(obj);

    character::power::essence sut;
    sut.read_from_json(obj);

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
}
