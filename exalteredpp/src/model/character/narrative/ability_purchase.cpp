#include "character/narrative/ability_purchase.h"
#include "character.h"
#include "json_constants.h"

namespace character { namespace narrative {

    ability_purchase::ability_purchase(ability_names::detailed_ability ability, unsigned int amount)
      : _ability(ability), _amount(amount) { }

    ability_names::detailed_ability ability_purchase::ability() const
    {
      return  _ability;
    }

    unsigned int ability_purchase::amount() const
    {
      return _amount;
    }

    void ability_purchase::apply(std::shared_ptr<character> c)
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
      return ability_names::ABILITY_NAME.at(_ability.ability)
          + _ability.declination;
    }

    std::string ability_purchase::description() const
    {
      std::string declination = _ability.declination == ability_names::ability_declination::NO_DECLINATION
          ? " "
          : " (" + _ability.declination + ") ";
      char amount[2];
      _itoa_s(_amount, amount, 10);
      return ability_names::ABILITY_NAME.at(_ability.ability)
          + declination
          + amount;
    }

    ability_purchase::~ability_purchase() {}
}}
