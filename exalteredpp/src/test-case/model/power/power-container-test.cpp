#include "../thirdparty/catch/catch.hpp"
#include "power/power_container.h"

TEST_CASE("power_container")
{
  SECTION("should read and write correctly to JSON")
  {
    power::power_container stub(power::essence(),
                                           power::willpower(),
                                           power::health(10, 5),
                                           power::logos());

    power::power_container sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut.essence().permanent_essence()     == stub.essence().permanent_essence()     );
    REQUIRE(sut.essence().khan()                  == stub.essence().khan()                  );
    REQUIRE(sut.willpower().permanent_willpower() == stub.willpower().permanent_willpower() );
    REQUIRE(sut.willpower().temporary_willpower() == stub.willpower().temporary_willpower() );
    REQUIRE(sut.get_health().total_health()           == stub.get_health().total_health()           );
    REQUIRE(sut.get_health().current_health()         == stub.get_health().current_health()         );
    REQUIRE(sut.logos().logos()               == stub.logos().logos()               );
    REQUIRE(sut.logos().get_total_qabbalah()      == stub.logos().get_total_qabbalah()      );
  }

  SECTION("should allow object update via reference getters")
  {
    power::power_container sut(power::essence(),
                                           power::willpower(),
                                           power::health(10, 5),
                                           power::logos());

    REQUIRE_FALSE(sut.logos().logos() == 5);
    REQUIRE_FALSE(sut.willpower().permanent_willpower() == 15);
    REQUIRE_FALSE(sut.essence().permanent_essence() == 5);
    REQUIRE_FALSE(sut.get_health().total_health() == 50);

    sut.logos().set_logos(5);
    sut.willpower().set_permanent_willpower(15);
    sut.essence().set_permanent_essence(5);
    sut.get_health().set_total_health(50);

    REQUIRE(sut.logos().logos() == 5);
    REQUIRE(sut.willpower().permanent_willpower() == 15);
    REQUIRE(sut.essence().permanent_essence() == 5);
    REQUIRE(sut.get_health().total_health() == 50);

  }

  SECTION("should use const getters when the object is const")
  {
    const power::power_container sut(power::essence(),
                                           power::willpower(),
                                           power::health(10, 5),
                                           power::logos());

    // these getters create copy objects which are then modified
    REQUIRE_NOTHROW(sut.logos().set_logos(5)                   );
    REQUIRE_NOTHROW(sut.willpower().set_permanent_willpower(15));
    REQUIRE_NOTHROW(sut.essence().set_permanent_essence(5)     );
    REQUIRE_NOTHROW(sut.get_health().set_total_health(50)          );

    // the const objects was left unmodified
    REQUIRE(sut.logos().logos() != 5);
    REQUIRE(sut.willpower().permanent_willpower() != 15);
    REQUIRE(sut.essence().permanent_essence() != 5);
    REQUIRE(sut.get_health().total_health() != 50);
  }
}
