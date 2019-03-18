#include "../thirdparty/catch/catch.hpp"
#include <filesystem_db.h>

#define CHARACTER_NAME "He who Cries Silver Tears"

TEST_CASE("filesystem_db")
{
  SECTION("should load test character")
  {
    serialisation::filesystem_db sut;
    QSharedPointer<character::character> stub_character(new character::character(CHARACTER_NAME));
    sut.save_character(stub_character);
    QSharedPointer<character::character> result = sut.load_character(CHARACTER_NAME);
    REQUIRE(result->getName() == CHARACTER_NAME);
  }
}
