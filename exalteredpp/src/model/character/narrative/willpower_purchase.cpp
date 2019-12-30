#include "narrative/willpower_purchase.h"
#include "character.h"
#include "text/character_text_constants.h"

namespace character { namespace narrative {

    willpower_purchase::willpower_purchase(unsigned int amount)
      : _amount(amount) { }

    willpower_purchase::~willpower_purchase() { }

    void willpower_purchase::apply(std::shared_ptr<character> c)
    {
      c->get_willpower().set_permanent_willpower(_amount);
    }

    void willpower_purchase::serialisation()
    {
      synch("amount", _amount);
    }

    unsigned int willpower_purchase::amount() const
    {
      return _amount;
    }

    std::string willpower_purchase::key() const
    {
      return model::text::character::WILLPOWER;
    }

    std::string willpower_purchase::description() const
    {
      char amount[2];
      _itoa_s(_amount, amount, 10);
      return model::text::character::WILLPOWER + " (" + amount + ")";
    }

}}
