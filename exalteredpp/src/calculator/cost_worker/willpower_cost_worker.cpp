#include "cost_worker/willpower_cost_worker.h"

namespace calculator { namespace cost {

    unsigned int willpower_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      auto current_willpower = character->get_willpower().permanent_willpower();

      return current_willpower * STANDARD_MULTIPLIER;
    }

}}
