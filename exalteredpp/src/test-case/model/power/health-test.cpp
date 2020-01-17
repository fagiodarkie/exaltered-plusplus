#include "../thirdparty/catch/catch.hpp"
#include "power/health.h"

TEST_CASE("health")
{
  SECTION("should create health with default values")
  {
    power::health sut(10);
    REQUIRE(sut.total_health() == 10);
    REQUIRE(sut.current_health() == 10);

    power::health sut_2(10, 5);
    REQUIRE(sut_2.total_health() == 10);
    REQUIRE(sut_2.current_health() == 5);
  }

  SECTION("should create health from JSON object")
  {
    power::health stub(10, 5);

    power::health sut(1);
    sut.deserialise(stub.serialise());

    REQUIRE(stub.current_health() == sut.current_health());
    REQUIRE(stub.total_health() == sut.total_health());
  }

  SECTION("should deal and heal damage")
  {
    power::health sut(10);
    REQUIRE(sut.current_health() == 10);
    REQUIRE(sut.current_health_penalty() == 0);

    sut.deal_damage(5);
    REQUIRE(sut.current_health() == 5);
    REQUIRE(sut.current_health_penalty() == 2);

    sut.deal_damage(3);
    REQUIRE(sut.current_health() == 2);
    REQUIRE(sut.current_health_penalty() == 4);

    sut.deal_damage(4);
    REQUIRE(sut.current_health() == 0);
    REQUIRE(sut.current_health_penalty() == 4);

    sut.heal_damage(5);
    REQUIRE(sut.current_health() == 5);
    REQUIRE(sut.current_health_penalty() == 2);

    sut.heal_damage(5);
    REQUIRE(sut.current_health() == 10);
    REQUIRE(sut.current_health_penalty() == 0);

    sut.heal_damage(5);
    REQUIRE(sut.current_health() == 10);
    REQUIRE(sut.current_health_penalty() == 0);

    sut.set_total_health(15);
    sut.heal_damage(5);
    REQUIRE(sut.current_health() == 15);
    REQUIRE(sut.current_health_penalty() == 0);
  }
}
