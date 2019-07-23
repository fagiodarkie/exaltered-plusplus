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

    character::virtues::virtues sut;
    sut.deserialise(stub.serialise());

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

  SECTION("should assign properly with copy constructor and assignment operator")
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

    character::virtues::virtues sut_1(stub);
    character::virtues::virtues sut_2;
    sut_2 = stub;

    REQUIRE(stub.vice()                                          == sut_1.vice());
    REQUIRE(stub.vice_value()                                    == sut_1.vice_value());
    REQUIRE(stub.value(character::virtues::COMPASSION).rank()    == sut_1.value(character::virtues::COMPASSION).rank()   );
    REQUIRE(stub.value(character::virtues::COMPASSION).value()   == sut_1.value(character::virtues::COMPASSION).value()  );
    REQUIRE(stub.value(character::virtues::CONVINCTION).rank()   == sut_1.value(character::virtues::CONVINCTION).rank()  );
    REQUIRE(stub.value(character::virtues::CONVINCTION).value()  == sut_1.value(character::virtues::CONVINCTION).value() );
    REQUIRE(stub.value(character::virtues::TEMPERANCE).rank()    == sut_1.value(character::virtues::TEMPERANCE).rank()   );
    REQUIRE(stub.value(character::virtues::TEMPERANCE).value()   == sut_1.value(character::virtues::TEMPERANCE).value()  );
    REQUIRE(stub.value(character::virtues::VALOR).rank()         == sut_1.value(character::virtues::VALOR).rank()        );
    REQUIRE(stub.value(character::virtues::VALOR).value()        == sut_1.value(character::virtues::VALOR).value()       );

    REQUIRE(stub.vice()                                          == sut_2.vice());
    REQUIRE(stub.vice_value()                                    == sut_2.vice_value());
    REQUIRE(stub.value(character::virtues::COMPASSION).rank()    == sut_2.value(character::virtues::COMPASSION).rank()   );
    REQUIRE(stub.value(character::virtues::COMPASSION).value()   == sut_2.value(character::virtues::COMPASSION).value()  );
    REQUIRE(stub.value(character::virtues::CONVINCTION).rank()   == sut_2.value(character::virtues::CONVINCTION).rank()  );
    REQUIRE(stub.value(character::virtues::CONVINCTION).value()  == sut_2.value(character::virtues::CONVINCTION).value() );
    REQUIRE(stub.value(character::virtues::TEMPERANCE).rank()    == sut_2.value(character::virtues::TEMPERANCE).rank()   );
    REQUIRE(stub.value(character::virtues::TEMPERANCE).value()   == sut_2.value(character::virtues::TEMPERANCE).value()  );
    REQUIRE(stub.value(character::virtues::VALOR).rank()         == sut_2.value(character::virtues::VALOR).rank()        );
    REQUIRE(stub.value(character::virtues::VALOR).value()        == sut_2.value(character::virtues::VALOR).value()       );
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
    REQUIRE(static_cast<const character::virtues::virtue>(stub[character::virtues::VALOR]).rank() == character::virtues::CHILD);
    REQUIRE(static_cast<const character::virtues::virtue>(stub[character::virtues::VALOR]).value() == 3);
  }

  SECTION("will not throw if one tries to access a non-initialised virtue")
  {
    character::virtues::virtues sut;

    REQUIRE_NOTHROW(static_cast<const character::virtues::virtue>(sut[character::virtues::VALOR]).rank());
    REQUIRE_NOTHROW(sut[character::virtues::VALOR].set_value(3));
  }
}
