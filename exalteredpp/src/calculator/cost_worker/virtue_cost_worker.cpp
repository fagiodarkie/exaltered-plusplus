#include "cost_worker/virtue_cost_worker.h"

#include "narrative/virtue_purchase.h"

namespace calculator { namespace cost {

    unsigned int virtue_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      auto ability = dynamic_cast<narrative::virtue_purchase*>(_purchase.get());

      auto virtue = ability->virtue();

      auto current_virtue = character->get_virtue(virtue).value();

      return current_virtue * STANDARD_MULTIPLIER;
    }

}}
