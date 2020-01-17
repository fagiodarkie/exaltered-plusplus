#include "cost_worker/ability_cost_worker.h"

#include "narrative/ability_purchase.h"

namespace calculator { namespace cost {

    unsigned int ability_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      unsigned int cost = 0;
      auto ability = dynamic_cast<narrative::ability_purchase*>(_purchase.get());

      auto ability_name = ability->ability();
      auto discount = (character->get(ability_name).favored()) ? FAVORITE_DISCOUNT : 0;

      for (int value = character->get(ability_name); value < _purchase->amount(); ++value)
        {
          if (value == 0)
            {
              cost += FIRST_DOT;
              continue;
            }

          cost += (value * STANDARD_MULTIPLIER) - discount;
        }

      return cost;
    }

}}
