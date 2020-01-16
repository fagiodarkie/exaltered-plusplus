#include "../thirdparty/catch/catch.hpp"
#include "power/logos.h"

TEST_CASE("logos")
{
  SECTION("should create logos object consistently")
  {
    power::logos sut(1, 2, 3, 4, 6, 5);

    REQUIRE(sut.get_logos()                         == 1);
    REQUIRE(sut.get_current_qabbalah()              == 2);
    REQUIRE(sut.get_total_qabbalah()                == 3);
    REQUIRE(sut.get_absolute_principle_connection() == 4);
    REQUIRE(sut.get_total_cyrcadian_rhythm()        == 6);
    REQUIRE(sut.get_current_cyrcadian_rhythm()      == 1);
  }

  SECTION("should read and write from JSON object")
  {
    power::logos stub(1, 2, 3, 4, 6, 5);

    power::logos sut;
    sut.deserialise(stub.serialise());

    REQUIRE(sut.get_logos()                         == stub.get_logos()                        );
    REQUIRE(sut.get_current_qabbalah()              == stub.get_current_qabbalah()             );
    REQUIRE(sut.get_total_qabbalah()                == stub.get_total_qabbalah()               );
    REQUIRE(sut.get_absolute_principle_connection() == stub.get_absolute_principle_connection());
    REQUIRE(sut.get_total_cyrcadian_rhythm()        == stub.get_total_cyrcadian_rhythm()       );
    REQUIRE(sut.get_current_cyrcadian_rhythm()      == stub.get_current_cyrcadian_rhythm()     );
  }
}
