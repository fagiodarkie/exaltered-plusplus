#include "narrative/specialisation_purchase.h"
#include "json_constants.h"
#include "character.h"
#include "abilities/specialisation.h"

namespace character { namespace narrative {

    specialisation_purchase::specialisation_purchase(unsigned int amount, ability_names::ability_enum ability, const std::string& specialisation)
      : _amount(amount), _ability(ability), _specialisation(specialisation) { }

    specialisation_purchase::~specialisation_purchase() { }

    void specialisation_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_AMOUNT, _amount);
      synch(serialisation::json_constants::SLOT_SPECIALISATION, _specialisation);
      synch(serialisation::json_constants::SLOT_ABILITY, _ability);
    }

    void specialisation_purchase::apply(std::shared_ptr<character> c)
    {
      c->get_ability_group(_ability).add_specialisation(specialisation(_specialisation, _amount));
    }

    std::string specialisation_purchase::key() const
    {
      return ability_names::ABILITY_NAME.at(_ability) + _specialisation;
    }

    std::string specialisation_purchase::description() const
    {
      char amount[1];
      sprintf(amount, "%d", _amount);
      return ability_names::ABILITY_NAME.at(_ability)
          + " ("
          + _specialisation
          + ") "
          + amount;
    }

} }
