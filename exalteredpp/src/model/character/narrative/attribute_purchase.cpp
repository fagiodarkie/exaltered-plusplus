#include "narrative/attribute_purchase.h"
#include "json_constants.h"
#include "character.h"

namespace character { namespace narrative {


    attribute_purchase::attribute_purchase(unsigned int amount, attribute_names::attribute attribute)
      : _amount(amount), _attribute(attribute) { }

    attribute_purchase::~attribute_purchase() { }

    void attribute_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
      synch(serialisation::json_constants::SLOT_ATTRIBUTE, _attribute);
    }

    void attribute_purchase::apply(std::shared_ptr<character> c)
    {
      c->get_attribute(_attribute).set_value(_amount);
    }

    std::string attribute_purchase::key() const
    {
      return attribute_names::ATTRIBUTE_NAME.at(_attribute);
    }

    attribute_names::attribute attribute_purchase::attribute() const
    {
      return _attribute;
    }

    std::string attribute_purchase::description() const
    {
      char amount[2];
      sprintf(amount, "%d", _amount);
      return key() + " (" + amount + ") ";
    }

} }
