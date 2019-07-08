#include "../thirdparty/catch/catch.hpp"
#include "virtues/virtues.h"
#include "serialisation/json_constants.h"

TEST_CASE("virtues")
{
  SECTION("should create virtues map on creation")
  {
    character::virtues::virtues sut;
    for (auto virtue : character::virtues::VIRTUE_LIST)
      REQUIRE(sut.value(virtue).virtue_type() == virtue);
  }

  SECTION("should read JSON file accordingly")
  {
    character::virtues::virtues stub;
    stub.set_vice_type(character::virtues::LUST);
    stub.set_vice_value(5);
    stub.value(character::virtues::COMPASSION).set_rank(character::virtues::ADULT);
    stub.value(character::virtues::COMPASSION).set_value(1);
    stub.value(character::virtues::CONVINCTION).set_rank(character::virtues::TEENAGER);
    stub.value(character::virtues::CONVINCTION).set_value(2);
    stub.value(character::virtues::TEMPERANCE).set_rank(character::virtues::SENIOR);
    stub.value(character::virtues::TEMPERANCE).set_value(3);
    stub.value(character::virtues::VALOR).set_rank(character::virtues::CHILD);
    stub.value(character::virtues::VALOR).set_value(4);

    QJsonObject obj;
    stub.write_to_json(obj);

    character::virtues::virtues sut;
    sut.read_from_json(obj);

    REQUIRE(stub.vice() == sut.vice());
    REQUIRE(stub.vice_value() == sut.vice_value());
    REQUIRE(stub.value(character::virtues::COMPASSION).rank()    == sut.value(character::virtues::COMPASSION).rank()   );
    REQUIRE(stub.value(character::virtues::COMPASSION).value()   == sut.value(character::virtues::COMPASSION).value()  );
    REQUIRE(stub.value(character::virtues::CONVINCTION).rank()   == sut.value(character::virtues::CONVINCTION).rank()  );
    REQUIRE(stub.value(character::virtues::CONVINCTION).value()  == sut.value(character::virtues::CONVINCTION).value() );
    REQUIRE(stub.value(character::virtues::TEMPERANCE).rank()    == sut.value(character::virtues::TEMPERANCE).rank()   );
    REQUIRE(stub.value(character::virtues::TEMPERANCE).value()   == sut.value(character::virtues::TEMPERANCE).value()  );
    REQUIRE(stub.value(character::virtues::VALOR).rank()         == sut.value(character::virtues::VALOR).rank()        );
    REQUIRE(stub.value(character::virtues::VALOR).value()        == sut.value(character::virtues::VALOR).value()       );
  }

  SECTION("should set and get values")
  {
    character::virtues::virtues stub;
    stub.set_vice_type(character::virtues::LUST);
    stub.set_vice_value(5);
    stub.value(character::virtues::COMPASSION).set_rank(character::virtues::ADULT);
    stub.value(character::virtues::COMPASSION).set_value(1);
    // also check square brackets setters
    stub[character::virtues::VALOR].set_rank(character::virtues::CHILD);
    stub[character::virtues::VALOR].set_value(3);

    REQUIRE(stub.vice() == character::virtues::LUST);
    REQUIRE(stub.vice_value() == 5);
    REQUIRE(stub.value(character::virtues::COMPASSION).rank() == character::virtues::ADULT);
    REQUIRE(stub.value(character::virtues::COMPASSION).value() == 1);
    // also check square brackets getters
    REQUIRE(stub[character::virtues::VALOR].rank() == character::virtues::CHILD);
    REQUIRE(stub[character::virtues::VALOR].value() == 3);
  }
}
