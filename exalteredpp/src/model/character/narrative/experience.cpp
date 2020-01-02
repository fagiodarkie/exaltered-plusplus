#include "character/narrative/experience.h"

#include "narrative/ability_purchase.h"
#include "narrative/attribute_purchase.h"
#include "narrative/virtue_purchase.h"
#include "narrative/vice_purchase.h"
#include "narrative/willpower_purchase.h"
#include "narrative/charm_purchase.h"
#include "narrative/background_purchase.h"
#include "narrative/specialisation_purchase.h"
#include "narrative/essence_purchase.h"

#include "json_constants.h"

namespace character { namespace narrative {

    experience_purchase::experience_purchase(experience_expense_type expense_type, unsigned int cost, std::shared_ptr<abstract_purchase> purchase)
      : _expense_type(expense_type), _cost(cost), _purchase(purchase) { }

    experience_purchase::~experience_purchase() { }

    void experience_purchase::serialisation()
    {
      synch(serialisation::json_constants::SLOT_TYPE, _expense_type);
      synch(serialisation::json_constants::SLOT_COST, _cost);

      switch(_expense_type)
        {
        case ABILITY:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<ability_purchase&>(*_purchase)); break;
        case ATTRIBUTE:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<attribute_purchase&>(*_purchase)); break;
        case SPECIALISATION:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<specialisation_purchase&>(*_purchase)); break;
        case CHARM:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<charm_purchase&>(*_purchase)); break;
        case BACKGROUND:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<background_purchase&>(*_purchase)); break;
        case VIRTUE:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<virtue_purchase&>(*_purchase)); break;
        case VICE:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<vice_purchase&>(*_purchase)); break;
        case WILLPOWER:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<willpower_purchase&>(*_purchase)); break;
        case ESSENCE:
          synch(serialisation::json_constants::SLOT_PURCHASE, static_cast<essence_purchase&>(*_purchase)); break;
        default:
          break;
        }
    }

    unsigned int experience_purchase::cost() const
    {
      return _cost;
    }

    experience_expense_type experience_purchase::purchase_type() const
    {
      return _expense_type;
    }

    std::shared_ptr<abstract_purchase> experience_purchase::purchase() const
    {
      return _purchase;
    }

}}
