#include "narrative/essence_purchase.h"
#include "character.h"
#include "text/character_text_constants.h"
#include "json_constants.h"

namespace narrative {

    essence_purchase::essence_purchase(unsigned int amount)
      : _amount(amount) { }

    unsigned int essence_purchase::amount() const
    {
      return _amount;
    }

    void essence_purchase::apply(std::shared_ptr<character::character> c)
    {
      c->essence().set_permanent_essence(_amount);
    }

    void essence_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
    }

    std::string essence_purchase::key() const
    {
      return model::text::ESSENCE;
    }

    std::string essence_purchase::description() const
    {
      return key() + " " + progress(_amount);
    }

    essence_purchase::~essence_purchase() {}
}
