#include "../thirdparty/catch/catch.hpp"

#include "error_codes.h"
#include "characternotfoundexception.h"

TEST_CASE("Exceptions")
{
  SECTION("character_not_found_exception")
  {
    exception::character_not_found_exception sut;
    REQUIRE(strcmp(sut.what(), error_code::serialisation::CHARACTER_NOT_FOUND) == 0);

    REQUIRE(strcmp(sut.clone()->what(), error_code::serialisation::CHARACTER_NOT_FOUND) == 0);

    try {
      sut.raise();
    } catch (QException& e) {
      REQUIRE(strcmp(e.what(), error_code::serialisation::CHARACTER_NOT_FOUND) == 0);
    }
  }
}
