#include "cost_worker/essence_cost_worker.h"

namespace calculator { namespace cost {

    unsigned int essence_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      return character->get_essence().permanent_essence() * STANDARD_MULTIPLIER;
    }

}}
