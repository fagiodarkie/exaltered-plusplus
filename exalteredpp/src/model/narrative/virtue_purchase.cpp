#include "narrative/virtue_purchase.h"
#include "json_constants.h"
#include "character.h"

namespace narrative {

    virtue_purchase::virtue_purchase(unsigned int amount, virtues::virtue_enum virtue)
      : _amount(amount), _virtue(virtue) { }

    virtue_purchase::~virtue_purchase() { }

    void virtue_purchase::apply(std::shared_ptr<character::character> c)
    {
      c->virtue(_virtue).set_value(_amount);
    }

    void virtue_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
      synch(serialisation::json_constants::SLOT_VIRTUE, _virtue);
    }

    std::string virtue_purchase::description() const
    {
      return key() + " " + progress(_amount);
    }

    std::string virtue_purchase::key() const
    {
      return virtues::VIRTUE_NAME.at(_virtue);
    }

    unsigned int virtue_purchase::amount() const
    {
      return _amount;
    }

    virtues::virtue_enum virtue_purchase::virtue() const
    {
      return _virtue;
    }

}
