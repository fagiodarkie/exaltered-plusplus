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

namespace character { namespace narrative {

    experience::experience(experience_expense_type expense_type, unsigned int cost, std::shared_ptr<abstract_purchase> purchase)
      : _expense_type(expense_type), _cost(cost), _purchase(purchase) { }

    experience::~experience() { }

    void experience::serialisation()
    {
      synch("type", _expense_type);
      synch("cost", _cost);

      switch(_expense_type)
        {
        case ABILITY:
          synch("purchase", static_cast<ability_purchase&>(*_purchase)); break;
        case ATTRIBUTE:
          synch("purchase", static_cast<attribute_purchase&>(*_purchase)); break;
        case SPECIALISATION:
          synch("purchase", static_cast<specialisation_purchase&>(*_purchase)); break;
        case CHARM:
          synch("purchase", static_cast<charm_purchase&>(*_purchase)); break;
        case BACKGROUND:
          synch("purchase", static_cast<background_purchase&>(*_purchase)); break;
        case VIRTUE:
          synch("purchase", static_cast<virtue_purchase&>(*_purchase)); break;
        case VICE:
          synch("purchase", static_cast<vice_purchase&>(*_purchase)); break;
        case WILLPOWER:
          synch("purchase", static_cast<willpower_purchase&>(*_purchase)); break;
        case ESSENCE:
          synch("purchase", static_cast<essence_purchase&>(*_purchase)); break;
        default:
          break;
        }
    }

    unsigned int experience::cost() const
    {
      return _cost;
    }

    experience_expense_type experience::purchase_type() const
    {
      return _expense_type;
    }

    std::shared_ptr<abstract_purchase> experience::purchase() const
    {
      return _purchase;
    }

}}
