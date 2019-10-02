#include "../thirdparty/catch/catch.hpp"
#include "common/reverse_search.h"

using namespace commons;

TEST_CASE("reverse search")
{
  SECTION("should reverse search within a list or a vector")
  {
    std::list<int> test = {1, 2, 3, 4, 5};
    std::vector<int> test_vector = {1, 2, 3, 4, 5};

    std::map<int, std::string> test_map = {
      {1, "1"},
      {2, "2"},
      {3, "3"},
      {4, "4"},
      {5, "5"}
    };

    REQUIRE(reverse_search_in_map(test, test_map, "3") == 3);
    REQUIRE(reverse_search_in_map(test_vector, test_map, "3") == 3);

    REQUIRE_THROWS(reverse_search_in_map(test, test_map, "6"));
    REQUIRE_THROWS(reverse_search_in_map(test_vector, test_map, "6"));
  }
}

TEST_CASE("contains")
{
  SECTION("should find an item in a list or vector")
  {
    std::list<int> test = {1, 2, 3, 4, 5};
    std::vector<int> test_vector = {1, 2, 3, 4, 5};

    REQUIRE(contains(test, 3));
    REQUIRE_FALSE(contains(test, 6));

    REQUIRE(contains(test_vector, 3));
    REQUIRE_FALSE(contains(test_vector, 6));
  }
}
