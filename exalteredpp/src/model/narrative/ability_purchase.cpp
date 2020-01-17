#include "narrative/ability_purchase.h"
#include "character.h"
#include "json_constants.h"

namespace narrative {

    ability_purchase::ability_purchase(ability::ability_name ability, unsigned int amount)
      : _ability(ability), _amount(amount) { }

    ability::ability_name ability_purchase::ability() const
    {
      return  _ability;
    }

    unsigned int ability_purchase::amount() const
    {
      return _amount;
    }

    void ability_purchase::apply(std::shared_ptr<character::character> c)
    {
      c->set(_ability, _amount);
    }

    void ability_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
      synch(serialisation::json_constants::SLOT_ABILITY, _ability);
    }

    std::string ability_purchase::key() const
    {
      return _ability.name();
    }

    std::string ability_purchase::description() const
    {
      return key() + " " + progress(_amount);
    }

    ability_purchase::~ability_purchase() {}
}
