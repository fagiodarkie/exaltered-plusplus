#include "narrative/willpower_purchase.h"
#include "character.h"
#include "text/character_text_constants.h"
#include "json_constants.h"

namespace narrative {

    willpower_purchase::willpower_purchase(unsigned int amount)
      : _amount(amount) { }

    willpower_purchase::~willpower_purchase() { }

    void willpower_purchase::apply(std::shared_ptr<character::character> c)
    {
      c->willpower().set_permanent_willpower(_amount);
    }

    void willpower_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
    }

    unsigned int willpower_purchase::amount() const
    {
      return _amount;
    }

    std::string willpower_purchase::key() const
    {
      return model::text::WILLPOWER;
    }

    std::string willpower_purchase::description() const
    {
      return model::text::WILLPOWER + progress(_amount);
    }

}
