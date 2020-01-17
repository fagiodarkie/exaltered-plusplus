#include "cost_worker/vice_cost_worker.h"

namespace calculator { namespace cost {

    unsigned int vice_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      unsigned int result = 0;
      for (int value = character->vice_value(); value < _purchase->amount(); ++value)
        result += value * STANDARD_MULTIPLIER;
      return result;
    }

}}
