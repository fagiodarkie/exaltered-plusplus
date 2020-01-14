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

    REQUIRE(sut.get_essence().permanent_essence()     == stub.get_essence().permanent_essence()     );
    REQUIRE(sut.get_essence().khan()                  == stub.get_essence().khan()                  );
    REQUIRE(sut.get_willpower().permanent_willpower() == stub.get_willpower().permanent_willpower() );
    REQUIRE(sut.get_willpower().temporary_willpower() == stub.get_willpower().temporary_willpower() );
    REQUIRE(sut.get_health().total_health()           == stub.get_health().total_health()           );
    REQUIRE(sut.get_health().current_health()         == stub.get_health().current_health()         );
    REQUIRE(sut.get_logos().get_logos()               == stub.get_logos().get_logos()               );
    REQUIRE(sut.get_logos().get_total_qabbalah()      == stub.get_logos().get_total_qabbalah()      );
  }

  SECTION("should allow object update via reference getters")
  {
    power::power_container sut(power::essence(),
                                           power::willpower(),
                                           power::health(10, 5),
                                           power::logos());

    REQUIRE_FALSE(sut.get_logos().get_logos() == 5);
    REQUIRE_FALSE(sut.get_willpower().permanent_willpower() == 15);
    REQUIRE_FALSE(sut.get_essence().permanent_essence() == 5);
    REQUIRE_FALSE(sut.get_health().total_health() == 50);

    sut.get_logos().set_logos(5);
    sut.get_willpower().set_permanent_willpower(15);
    sut.get_essence().set_permanent_essence(5);
    sut.get_health().set_total_health(50);

    REQUIRE(sut.get_logos().get_logos() == 5);
    REQUIRE(sut.get_willpower().permanent_willpower() == 15);
    REQUIRE(sut.get_essence().permanent_essence() == 5);
    REQUIRE(sut.get_health().total_health() == 50);

  }

  SECTION("should use const getters when the object is const")
  {
    const power::power_container sut(power::essence(),
                                           power::willpower(),
                                           power::health(10, 5),
                                           power::logos());

    // these getters create copy objects which are then modified
    REQUIRE_NOTHROW(sut.get_logos().set_logos(5)                   );
    REQUIRE_NOTHROW(sut.get_willpower().set_permanent_willpower(15));
    REQUIRE_NOTHROW(sut.get_essence().set_permanent_essence(5)     );
    REQUIRE_NOTHROW(sut.get_health().set_total_health(50)          );

    // the const objects was left unmodified
    REQUIRE(sut.get_logos().get_logos() != 5);
    REQUIRE(sut.get_willpower().permanent_willpower() != 15);
    REQUIRE(sut.get_essence().permanent_essence() != 5);
    REQUIRE(sut.get_health().total_health() != 50);
  }
}
