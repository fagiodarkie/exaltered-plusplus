#include "cost_worker/willpower_cost_worker.h"

namespace calculator { namespace cost {

    unsigned int willpower_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      unsigned int result = 0;
      auto current_willpower = character->willpower().permanent_willpower();
      while (current_willpower < _purchase->amount())
        {
          result += current_willpower++ * STANDARD_MULTIPLIER;
        }

      return result;
    }

}}
