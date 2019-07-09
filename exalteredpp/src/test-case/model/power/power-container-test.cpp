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

    REQUIRE(sut.get_essence().permanent_essence()     == stub.get_essence().permanent_essence()     );
    REQUIRE(sut.get_essence().khan()                  == stub.get_essence().khan()                  );
    REQUIRE(sut.get_willpower().permanent_willpower() == stub.get_willpower().permanent_willpower() );
    REQUIRE(sut.get_willpower().temporary_willpower() == stub.get_willpower().temporary_willpower() );
    REQUIRE(sut.get_health().total_health()           == stub.get_health().total_health()           );
    REQUIRE(sut.get_health().current_health()         == stub.get_health().current_health()         );
    REQUIRE(sut.get_logos().get_logos()               == stub.get_logos().get_logos()               );
    REQUIRE(sut.get_logos().get_total_qabbalah()      == stub.get_logos().get_total_qabbalah()      );
  }
}
