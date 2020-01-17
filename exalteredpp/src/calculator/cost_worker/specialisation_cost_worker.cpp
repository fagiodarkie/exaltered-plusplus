#include "cost_worker/specialisation_cost_worker.h"

#include "narrative/specialisation_purchase.h"

#include <narrative/specialisation_purchase.h>

namespace calculator { namespace cost {

    unsigned int specialisation_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      auto purchase = dynamic_cast<narrative::specialisation_purchase*>(_purchase.get());
      auto ability = purchase->ability();
      auto spec_name = purchase->specialisation_name();

      unsigned int result = 0;
      for (int value = character->get(ability).get(spec_name); value < _purchase->amount(); ++value)
        result += STANDARD_COST;

      return result;
    }

}}
