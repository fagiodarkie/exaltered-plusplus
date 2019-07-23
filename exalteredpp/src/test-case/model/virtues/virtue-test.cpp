#include "../thirdparty/catch/catch.hpp"
#include "virtues/virtue.h"

#include <QJsonDocument>

TEST_CASE("virtue")
{
  SECTION("should create virtue with proper values")
  {
    character::virtues::virtue sut(character::virtues::COMPASSION, 2, character::virtues::ADULT);
    REQUIRE(sut.rank() == character::virtues::ADULT);
    REQUIRE(sut.value() == 2);
    REQUIRE(sut.virtue_type() == character::virtues::COMPASSION);
  }

  SECTION("should create virtue from JSON object")
  {
    character::virtues::virtue stub(character::virtues::COMPASSION, 2, character::virtues::ADULT);

    character::virtues::virtue sut(stub.serialise());
    REQUIRE(sut.rank() == stub.rank());
    REQUIRE(sut.value() == stub.value());
    REQUIRE(sut.virtue_type() == stub.virtue_type());
  }
}
