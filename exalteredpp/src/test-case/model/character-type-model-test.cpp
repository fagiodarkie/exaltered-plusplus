#include "../thirdparty/catch/catch.hpp"

#include "creation/character_type_model.h"

TEST_CASE("Character type model")
{
  SECTION("should map each type of character to a model")
  {
    for (auto char_type : character::creation::CHARACTER_TYPE_NAMES.keys())
      {
        REQUIRE_NOTHROW(character::creation::character_type_model::get_by_character_type(char_type));
      }
  }
}
