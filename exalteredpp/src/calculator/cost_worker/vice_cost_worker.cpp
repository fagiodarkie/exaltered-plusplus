#include "cost_worker/vice_cost_worker.h"

namespace calculator { namespace cost {

    unsigned int vice_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      return character->vice_value() * STANDARD_MULTIPLIER;
    }

}}
