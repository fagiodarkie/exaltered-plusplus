#include "../thirdparty/catch/catch.hpp"

#include "exalt/exalt_caste.h"

TEST_CASE("exalt_caste")
{
  SECTION("all exalt castes are defined")
  {
    for (auto caste: character::exalt::CASTES)
      {
        try {
          auto resulting_caste = character::exalt::exalt_caste::get_caste(caste);
          REQUIRE_FALSE(resulting_caste.name().empty());
          REQUIRE_FALSE(((caste != character::exalt::caste::NO_CASTE)
                        && resulting_caste.abilities().empty()));
        } catch (...) {
          FAIL("some castes are not defined!");
        }
      }
  }
}
