#include "cost_worker/ability_cost_worker.h"

#include "narrative/ability_purchase.h"

namespace calculator { namespace cost {

    unsigned int ability_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      auto ability = dynamic_cast<character::narrative::ability_purchase*>(_purchase.get());

      auto ability_name = ability->ability();

      if (!character->has_ability(ability_name)
          || (character->get_ability(ability_name) == 0))
        return FIRST_DOT;

      auto current_ability = character->get_ability(ability_name);

      unsigned int cost = current_ability.get_ability_value() * STANDARD_MULTIPLIER;

      if (current_ability.is_favourite())
        cost -= FAVORITE_DISCOUNT;

      return cost;
    }

}}
