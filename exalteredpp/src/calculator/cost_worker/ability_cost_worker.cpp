#include "cost_worker/ability_cost_worker.h"

#include "narrative/ability_purchase.h"

namespace calculator { namespace cost {

    unsigned int ability_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      auto ability = dynamic_cast<narrative::ability_purchase*>(_purchase.get());

      auto ability_name = ability->ability();

      if (!character->has(ability_name)
          || (character->get(ability_name) == 0))
        return FIRST_DOT;

      auto current_ability = character->get(ability_name);

      unsigned int cost = current_ability.value() * STANDARD_MULTIPLIER;

      if (current_ability.favored())
        cost -= FAVORITE_DISCOUNT;

      return cost;
    }

}}
