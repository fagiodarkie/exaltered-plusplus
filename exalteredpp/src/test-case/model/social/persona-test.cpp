#include "../thirdparty/catch/catch.hpp"
#include "social/persona.h"

TEST_CASE("persona")
{
  SECTION("should create correctly with constructor")
  {
    character::social::persona sut(20, 7, 6, 5, 4, 3, 2, 1);

    REQUIRE(sut.get_persona() == 20);
    REQUIRE(sut.get_compulsions_specific() == 7);
    REQUIRE(sut.get_emotions_specific() == 6);
    REQUIRE(sut.get_illusions_specific() == 5);
    REQUIRE(sut.get_motivations_specific() == 4);
    REQUIRE(sut.get_serfdom_specific() == 3);
    REQUIRE(sut.get_max_philosophies() == 2);
    REQUIRE(sut.get_max_philosophy_value() == 1);
  }

  SECTION("should read and write JSON Object")
  {
    character::social::persona stub(20, 7, 6, 5, 4, 3, 2, 1);

    for (int i = 0; i < character::social::BASE_EMOTIONS.size(); ++i)
      {
        stub.set_base_emotion_bonus(character::social::BASE_EMOTIONS[i], i);
      }

    stub.add_philosophy(character::social::philosophy("phil_name", 1));

    QJsonObject obj;
    stub.write_to_json(obj);

    character::social::persona sut;
    sut.read_from_json(obj);

    REQUIRE(sut.get_persona              () == stub.get_persona              () );
    REQUIRE(sut.get_compulsions_specific () == stub.get_compulsions_specific () );
    REQUIRE(sut.get_emotions_specific    () == stub.get_emotions_specific    () );
    REQUIRE(sut.get_illusions_specific   () == stub.get_illusions_specific   () );
    REQUIRE(sut.get_motivations_specific () == stub.get_motivations_specific () );
    REQUIRE(sut.get_serfdom_specific     () == stub.get_serfdom_specific     () );
    REQUIRE(sut.get_max_philosophies     () == stub.get_max_philosophies     () );
    REQUIRE(sut.get_max_philosophy_value () == stub.get_max_philosophy_value () );

    for (auto emotion : character::social::BASE_EMOTIONS)
      REQUIRE(sut.get_emotion_bonus_for(emotion) == stub.get_emotion_bonus_for(emotion));

    for (auto philosophy : stub.philosophies())
      REQUIRE(sut.philosophies().contains(philosophy));
  }

  SECTION("should throw if attempts are made to insert more philosophies than allowed")
  {
    character::social::persona sut(20, 7, 6, 5, 4, 3, 2, 1);
    REQUIRE_NOTHROW(sut.add_philosophy(character::social::philosophy("p1", 1)));
    REQUIRE_NOTHROW(sut.add_philosophy(character::social::philosophy("p2", 1)));
    REQUIRE_THROWS(sut.add_philosophy(character::social::philosophy("p3", 1)));
  }

  SECTION("should ignore attempts to increase philosophies more than allowed")
  {
    character::social::persona sut(20, 7, 6, 5, 4, 3, 2, 1);
    REQUIRE_NOTHROW(sut.add_philosophy(character::social::philosophy("p1", 1)));
    REQUIRE_NOTHROW(sut.increase_philosophy("p1"));
    REQUIRE(sut.philosophies()[0].value() == 1);
  }

  SECTION("should increase and decrease philosophies")
  {
    character::social::persona sut(20, 7, 6, 5, 4, 3, 2, 4);
    REQUIRE_NOTHROW(sut.add_philosophy(character::social::philosophy("p1", 1)));
    sut.increase_philosophy("p1");
    REQUIRE(sut.philosophies()[0].value() == 2);
    sut.increase_philosophy("p1", 2);
    REQUIRE(sut.philosophies()[0].value() == 4);
    sut.decrease_philosophy("p1");
    REQUIRE(sut.philosophies()[0].value() == 3);
    sut.decrease_philosophy("p1", 2);
    REQUIRE(sut.philosophies()[0].value() == 1);
    sut.decrease_philosophy("p1");
    REQUIRE(sut.philosophies().isEmpty());
  }
}
