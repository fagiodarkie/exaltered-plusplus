#include "../thirdparty/catch/catch.hpp"
#include "power/power_container.h"

TEST_CASE("power_container")
{
  SECTION("should read and write correctly to JSON")
  {
    character::power::power_container stub(character::power::essence(),
                                           character::power::willpower(),
                                           character::power::health(10, 5),
                                           character::power::logos());

    QJsonObject obj;
    stub.write_to_json(obj);

    character::power::power_container sut;
    sut.read_from_json(obj);

    REQUIRE(sut.essence().permanent_essence()     == stub.essence().permanent_essence()     );
    REQUIRE(sut.essence().khan()                  == stub.essence().khan()                  );
    REQUIRE(sut.willpower().permanent_willpower() == stub.willpower().permanent_willpower() );
    REQUIRE(sut.willpower().temporary_willpower() == stub.willpower().temporary_willpower() );
    REQUIRE(sut.health().total_health()           == stub.health().total_health()           );
    REQUIRE(sut.health().current_health()         == stub.health().current_health()         );
  }
}
