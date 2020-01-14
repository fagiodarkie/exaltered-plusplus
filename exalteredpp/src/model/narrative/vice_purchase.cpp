#include "narrative/vice_purchase.h"
#include "json_constants.h"
#include "character.h"
#include "text/character_text_constants.h"

namespace character { namespace narrative {

    vice_purchase::vice_purchase(unsigned int amount)
      : _amount(amount) { }

    vice_purchase::~vice_purchase() { }

    void vice_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
    }

    void vice_purchase::apply(std::shared_ptr<character> c)
    {
      c->set_vice(c->get_vice(), _amount);
    }

    std::string vice_purchase::description() const
    {
      return model::text::character::VICE + " " + progress(_amount);
    }

    std::string vice_purchase::key() const
    {
      return model::text::character::VICE;
    }

}}