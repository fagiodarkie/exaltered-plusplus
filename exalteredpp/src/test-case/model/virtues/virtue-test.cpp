#include "../thirdparty/catch/catch.hpp"
#include "virtues/virtue.h"

#include <QJsonDocument>

TEST_CASE("virtue")
{
  SECTION("should create virtue with proper values")
  {
    virtues::virtue sut(virtues::COMPASSION, 2);
    REQUIRE(sut.value() == 2);
    REQUIRE(sut.virtue_type() == virtues::COMPASSION);
  }

  SECTION("should create virtue from JSON object")
  {
    virtues::virtue stub(virtues::COMPASSION, 2);

    virtues::virtue sut(stub.serialise());
    REQUIRE(sut.value() == stub.value());
    REQUIRE(sut.virtue_type() == stub.virtue_type());
  }
}
