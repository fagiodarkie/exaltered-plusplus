#include "narrative/vice_purchase.h"

#include "character.h"
#include "text/character_text_constants.h"

namespace character { namespace narrative {

    vice_purchase::vice_purchase(unsigned int amount)
      : _amount(amount) { }

    vice_purchase::~vice_purchase() { }

    void vice_purchase::serialisation()
    {
      synch("amount", _amount);
    }

    void vice_purchase::apply(std::shared_ptr<character> c)
    {
      c->set_vice(c->get_vice(), _amount);
    }

    std::string vice_purchase::description() const
    {
      char amount[1];
      _itoa_s(_amount, amount, 10);
      return model::text::character::VICE + " (" + amount + ")";
    }

    std::string vice_purchase::key() const
    {
      return model::text::character::VICE;
    }

}}
