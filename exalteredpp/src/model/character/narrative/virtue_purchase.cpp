#include "narrative/virtue_purchase.h"

#include "character.h"

namespace character { namespace narrative {

    virtue_purchase::virtue_purchase(unsigned int amount, virtues::virtue_enum virtue)
      : _amount(amount), _virtue(virtue) { }

    virtue_purchase::~virtue_purchase() { }

    void virtue_purchase::apply(std::shared_ptr<character> c)
    {
      c->get_virtue(_virtue).set_value(_amount);
    }

    void virtue_purchase::serialisation()
    {
      synch("amount", _amount);
      synch("virtue", _virtue);
    }

    std::string virtue_purchase::description() const
    {
      char amount[1];
      _itoa_s(_amount, amount, 10);
      return virtues::VIRTUE_NAME.at(_virtue) + " (" + amount + ")";
    }

    unsigned int virtue_purchase::amount() const
    {
      return _amount;
    }

    virtues::virtue_enum virtue_purchase::virtue() const
    {
      return _virtue;
    }

}}
