#include "../thirdparty/catch/catch.hpp"
#include <filesystem_db.h>

TEST_CASE("filesystem_db")
{
  SECTION("should load test character")
  {
    serialisation::filesystem_db sut;
    QSharedPointer<character::character> result = sut.load_character("test");
    REQUIRE(result->getName() == "test");
  }
}
