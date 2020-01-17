#pragma once

#include "character.h"
#include "narrative/experience.h"
#include <map>
#include "calculator/cost_worker/abstract_cost_worker.h"

namespace calculator {

  class purchase_cost_calculator
  {
  private:
    class experience_cost_inner_computation
    {
    public:
      experience_cost_inner_computation(narrative::experience_expense_type purchase_type,
                                        std::shared_ptr<narrative::abstract_purchase> purchase);

      unsigned int for_who(std::shared_ptr<character::character> character) const;

    private:
      std::shared_ptr<narrative::abstract_purchase> _purchase;
      narrative::experience_expense_type _purchase_type;

      static const std::map<
                  narrative::experience_expense_type,
                  std::shared_ptr<calculator::cost::abstract_cost_worker>> COST_WORKER_BY_EXPENSE_TYPE;

    };

  public:
    static experience_cost_inner_computation cost_of(narrative::experience_expense_type purchase_type,
                                                     std::shared_ptr<narrative::abstract_purchase> purchase);

  };

}


