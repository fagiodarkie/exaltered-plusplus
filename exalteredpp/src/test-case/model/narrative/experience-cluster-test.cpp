#include "../thirdparty/catch/catch.hpp"

#include "narrative/experience_cluster.h"

TEST_CASE("Experience Cluster")
{
  SECTION("should add award correctly")
  {
    narrative::experience_cluster sut;
    REQUIRE(sut.total_awarded() == 0);
    REQUIRE(sut.last_session() == 0);
    REQUIRE(sut.awards().size() == 0);
    narrative::session_awards session;
    session[narrative::PLAYTIME] = narrative::experience_award(narrative::PLAYTIME, 2);
    sut.award(session);
    REQUIRE(sut.total_awarded() == 2);
    REQUIRE(sut.last_session() == 1);
    REQUIRE(sut.awards().size() == 1);
  }

  SECTION("should correctly tell sessions apart")
  {
    narrative::experience_cluster sut;
    narrative::session_awards session1, session2, session3;
    session1[narrative::PLAYTIME] = narrative::experience_award(narrative::PLAYTIME, 2);
    session1[narrative::ACTING_OSCAR] = narrative::experience_award(narrative::ACTING_OSCAR, 6);
    session2[narrative::PLAYTIME] = narrative::experience_award(narrative::PLAYTIME, 4);
    session3[narrative::PLAYTIME] = narrative::experience_award(narrative::PLAYTIME, 6);
    session3[narrative::ACTING_OSCAR] = narrative::experience_award(narrative::ACTING_OSCAR, 4);
    sut.award(session1);
    sut.award(session2);
    sut.award(session3);
    REQUIRE(sut.awards().size() == 3);
    REQUIRE(sut.awarded_on_session(1) == 8);
    REQUIRE(sut.awarded_on_session(2) == 4);
    REQUIRE(sut.awarded_on_session(3) == 10);
    REQUIRE(sut.total_awarded() == 22);
  }

  SECTION("should add expense correctly")
  {
    narrative::experience_cluster sut;
    REQUIRE(sut.total_cost() == 0);
    REQUIRE(sut.purchases().size() == 0);
    sut.purchase(narrative::experience_purchase(narrative::ATTRIBUTE, 8));
    REQUIRE(sut.total_cost() == 8);
    REQUIRE(sut.purchases().size() == 1);
  }

  SECTION("should serialise and deserialise correctly")
  {
    narrative::experience_cluster stub;
    narrative::session_awards session1, session2, session3;
    session1[narrative::PLAYTIME] = narrative::experience_award(narrative::PLAYTIME, 2);
    session1[narrative::ACTING_OSCAR] = narrative::experience_award(narrative::ACTING_OSCAR, 6);
    session2[narrative::PLAYTIME] = narrative::experience_award(narrative::PLAYTIME, 4);
    session3[narrative::PLAYTIME] = narrative::experience_award(narrative::PLAYTIME, 6);
    session3[narrative::ACTING_OSCAR] = narrative::experience_award(narrative::ACTING_OSCAR, 4);
    stub.award(session1);
    stub.award(session2);
    stub.award(session3);

    stub.purchase(narrative::experience_purchase(narrative::ATTRIBUTE, 8));
    stub.purchase(narrative::experience_purchase(narrative::ABILITY, 5));
    stub.purchase(narrative::experience_purchase(narrative::SPECIALISATION, 3));

    std::string data = stub.serialise();

    narrative::experience_cluster sut;
    sut.deserialise(data);

    REQUIRE(sut.awards().size() == 3);
    REQUIRE(sut.awarded_on_session(1) == 8);
    REQUIRE(sut.awarded_on_session(2) == 4);
    REQUIRE(sut.awarded_on_session(3) == 10);
    REQUIRE(sut.total_awarded() == 22);
    REQUIRE(sut.purchases().size() == 3);
    REQUIRE(sut.total_cost() == 16);

  }
}
