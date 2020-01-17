#include "cost_worker/essence_cost_worker.h"

namespace calculator { namespace cost {

    unsigned int essence_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      unsigned int result = 0;
      for (int value = character->essence().permanent_essence(); value < _purchase->amount(); ++value)
        result += value * STANDARD_MULTIPLIER;
      return result;
    }

}}
