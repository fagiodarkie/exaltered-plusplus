#include "narrative/essence_purchase.h"
#include "character.h"
#include "text/character_text_constants.h"
#include "json_constants.h"

namespace character { namespace narrative {

    essence_purchase::essence_purchase(unsigned int amount)
      : _amount(amount) { }

    unsigned int essence_purchase::amount() const
    {
      return _amount;
    }

    void essence_purchase::apply(std::shared_ptr<character> c)
    {
      c->get_essence().set_permanent_essence(_amount);
    }

    void essence_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
    }

    std::string essence_purchase::key() const
    {
      return model::text::character::ESSENCE;
    }

    std::string essence_purchase::description() const
    {
      return key() + " " + progress(_amount);
    }

    essence_purchase::~essence_purchase() {}
}}
