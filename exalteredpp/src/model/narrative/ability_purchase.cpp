#include "narrative/ability_purchase.h"
#include "character.h"
#include "json_constants.h"

namespace narrative {

    ability_purchase::ability_purchase(ability::detailed_ability ability, unsigned int amount)
      : _ability(ability), _amount(amount) { }

    ability::detailed_ability ability_purchase::ability() const
    {
      return  _ability;
    }

    unsigned int ability_purchase::amount() const
    {
      return _amount;
    }

    void ability_purchase::apply(std::shared_ptr<character::character> c)
    {
      c->set_ability_value(_ability, _amount);
    }

    void ability_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
      synch(serialisation::json_constants::SLOT_ABILITY, _ability.ability);
      synch(serialisation::json_constants::SLOT_DECLINATION, _ability.declination);
    }

    std::string ability_purchase::key() const
    {
      return ability::ABILITY_NAME.at(_ability.ability)
          + _ability.declination;
    }

    std::string ability_purchase::description() const
    {
      return ability_string() + progress(_amount);
    }

    std::string ability_purchase::ability_string() const
    {
      std::string declination = _ability.declination == ability::ability_declination::NO_DECLINATION
          ? " "
          : " (" + _ability.declination + ") ";

      return ability::ABILITY_NAME.at(_ability.ability)
          + declination;
    }

    ability_purchase::~ability_purchase() {}
}
