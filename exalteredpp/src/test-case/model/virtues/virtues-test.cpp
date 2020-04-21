#include "../thirdparty/catch/catch.hpp"
#include "virtues/virtues.h"
#include "serialisation/json_constants.h"

TEST_CASE("virtues")
{
  virtues::virtues stub;
  stub.set_vice_type(virtues::LUST);
  stub.set_vice_value(5);
  stub.value(virtues::COMPASSION).set_value(1);
  stub.value(virtues::CONVINCTION).set_value(2);
  stub.value(virtues::TEMPERANCE).set_value(3);
  stub.value(virtues::VALOR).set_value(4);

  SECTION("should create virtues map on creation")
  {
    virtues::virtues sut;
    for (auto virtue : virtues::VIRTUE_LIST)
      REQUIRE(sut.value(virtue).virtue_type() == virtue);
  }

  SECTION("should read JSON file accordingly")
  {
    virtues::virtues sut;
    sut.deserialise(stub.serialise());

    REQUIRE(stub.vice() == sut.vice());
    REQUIRE(stub.vice_value() == sut.vice_value());
    REQUIRE(stub.value(virtues::COMPASSION).value()   == sut.value(virtues::COMPASSION).value()  );
    REQUIRE(stub.value(virtues::CONVINCTION).value()  == sut.value(virtues::CONVINCTION).value() );
    REQUIRE(stub.value(virtues::TEMPERANCE).value()   == sut.value(virtues::TEMPERANCE).value()  );
    REQUIRE(stub.value(virtues::VALOR).value()        == sut.value(virtues::VALOR).value()       );
  }

  SECTION("should assign properly with copy constructor and assignment operator")
  {
    virtues::virtues sut_1(stub);
    virtues::virtues sut_2;
    sut_2 = stub;

    REQUIRE(stub.vice()                                          == sut_1.vice());
    REQUIRE(stub.vice_value()                                    == sut_1.vice_value());
    REQUIRE(stub.value(virtues::COMPASSION).value()   == sut_1.value(virtues::COMPASSION).value()  );
    REQUIRE(stub.value(virtues::CONVINCTION).value()  == sut_1.value(virtues::CONVINCTION).value() );
    REQUIRE(stub.value(virtues::TEMPERANCE).value()   == sut_1.value(virtues::TEMPERANCE).value()  );
    REQUIRE(stub.value(virtues::VALOR).value()        == sut_1.value(virtues::VALOR).value()       );

    REQUIRE(stub.vice()                                          == sut_2.vice());
    REQUIRE(stub.vice_value()                                    == sut_2.vice_value());
    REQUIRE(stub.value(virtues::COMPASSION).value()   == sut_2.value(virtues::COMPASSION).value()  );
    REQUIRE(stub.value(virtues::CONVINCTION).value()  == sut_2.value(virtues::CONVINCTION).value() );
    REQUIRE(stub.value(virtues::TEMPERANCE).value()   == sut_2.value(virtues::TEMPERANCE).value()  );
    REQUIRE(stub.value(virtues::VALOR).value()        == sut_2.value(virtues::VALOR).value()       );
  }

  SECTION("should set and get values")
  {
    // also check square brackets setters
    stub[virtues::VALOR].set_value(3);

    REQUIRE(stub.vice() == virtues::LUST);
    REQUIRE(stub.vice_value() == 5);
    REQUIRE(stub.value(virtues::COMPASSION).value() == 1);
    // also check square brackets getters
    REQUIRE(static_cast<const virtues::virtues>(stub)[virtues::VALOR].value() == 3);
    REQUIRE(stub.value(virtues::VALOR).value() == 3);
  }

  SECTION("will not throw if one tries to access a non-initialised virtue")
  {
    virtues::virtues sut;

    REQUIRE_NOTHROW(sut[virtues::VALOR].set_value(3));
  }
}
