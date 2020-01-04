#include "cost_worker/specialisation_cost_worker.h"

#include "narrative/specialisation_purchase.h"

namespace calculator { namespace cost {

    unsigned int specialisation_cost_worker::cost_for(std::shared_ptr<character::character>) const
    {
      return STANDARD_COST;
    }

}}
