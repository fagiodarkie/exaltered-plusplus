#include "narrative/vice_purchase.h"
#include "json_constants.h"
#include "character.h"
#include "text/character_text_constants.h"

namespace narrative {

    vice_purchase::vice_purchase(unsigned int amount)
      : _amount(amount) { }

    vice_purchase::~vice_purchase() { }

    void vice_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
    }

    void vice_purchase::apply(std::shared_ptr<character::character> c)
    {
      c->set_vice(c->vice(), _amount);
    }

    unsigned int vice_purchase::amount() const
    {
      return _amount;
    }

    std::string vice_purchase::description() const
    {
      return model::text::VICE + " " + progress(_amount);
    }

    std::string vice_purchase::key() const
    {
      return model::text::VICE;
    }

}
