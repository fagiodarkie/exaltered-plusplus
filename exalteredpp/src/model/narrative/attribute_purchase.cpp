#include "narrative/attribute_purchase.h"
#include "json_constants.h"
#include "character.h"

namespace narrative {


    attribute_purchase::attribute_purchase(attribute::attribute_enum attribute, unsigned int amount)
      : _amount(amount), _attribute(attribute) { }

    attribute_purchase::~attribute_purchase() { }

    void attribute_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
      synch(serialisation::json_constants::SLOT_ATTRIBUTE, _attribute);
    }

    void attribute_purchase::apply(std::shared_ptr<character::character> c)
    {
      c->set(_attribute, _amount);
    }

    std::string attribute_purchase::key() const
    {
      return attribute::ATTRIBUTE_NAME.at(_attribute);
    }

    attribute::attribute_enum attribute_purchase::attribute() const
    {
      return _attribute;
    }

    unsigned int attribute_purchase::amount() const
    {
      return _amount;
    }

    std::string attribute_purchase::description() const
    {
      return key() + " " + progress(_amount);
    }

}
