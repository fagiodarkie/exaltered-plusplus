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
      auto purchase_pointer = _purchase.get();
      synch(serialisation::json_constants::SLOT_PURCHASE, purchase_pointer);
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
