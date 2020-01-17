#include "experience_purchase_cost_calculator.h"

#include "cost_worker/ability_cost_worker.h"
#include "cost_worker/attribute_cost_worker.h"
#include "cost_worker/specialisation_cost_worker.h"
#include "cost_worker/essence_cost_worker.h"
#include "cost_worker/virtue_cost_worker.h"
#include "cost_worker/vice_cost_worker.h"
#include "cost_worker/willpower_cost_worker.h"

namespace calculator {

  using namespace narrative;

  purchase_cost_calculator::experience_cost_inner_computation purchase_cost_calculator::cost_of(
      experience_expense_type purchase_type,
      std::shared_ptr<abstract_purchase> purchase)
  {
    return experience_cost_inner_computation(purchase_type, purchase);
  }

  const std::map< narrative::experience_expense_type,
                  std::shared_ptr<calculator::cost::abstract_cost_worker>>
  purchase_cost_calculator::experience_cost_inner_computation::COST_WORKER_BY_EXPENSE_TYPE = {

    { ATTRIBUTE,      std::make_shared<calculator::cost::attribute_cost_worker>       () },
    { ABILITY,        std::make_shared<calculator::cost::ability_cost_worker>         () },
    { SPECIALISATION, std::make_shared<calculator::cost::specialisation_cost_worker>  () },
    { VIRTUE,         std::make_shared<calculator::cost::virtue_cost_worker>          () },
    { VICE,           std::make_shared<calculator::cost::vice_cost_worker>            () },
    { ESSENCE,        std::make_shared<calculator::cost::essence_cost_worker>         () },
    { WILLPOWER,      std::make_shared<calculator::cost::willpower_cost_worker>       () }

  };

  purchase_cost_calculator::experience_cost_inner_computation::experience_cost_inner_computation(experience_expense_type purchase_type,
                                                                                                 std::shared_ptr<abstract_purchase> purchase)
    : _purchase(purchase), _purchase_type(purchase_type) { }

  unsigned int purchase_cost_calculator::experience_cost_inner_computation::for_who(std::shared_ptr<character::character> character) const
  {
    if (COST_WORKER_BY_EXPENSE_TYPE.find(_purchase_type) == COST_WORKER_BY_EXPENSE_TYPE.end())
      return 0;

    COST_WORKER_BY_EXPENSE_TYPE.at(_purchase_type)->with_purchase(_purchase);
    return COST_WORKER_BY_EXPENSE_TYPE.at(_purchase_type)->cost_for(character);
  }
}
