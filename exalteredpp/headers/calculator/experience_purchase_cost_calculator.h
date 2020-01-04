#pragma once

#include "character.h"
#include "narrative/experience.h"
#include <map>

namespace calculator {

  class purchase_cost_calculator
  {
  private:
    class experience_cost_inner_computation
    {
    public:
      experience_cost_inner_computation(const character::narrative::experience_purchase& purchase);

      unsigned int for_who(std::shared_ptr<character::character> character);

    private:
      std::shared_ptr<character::narrative::abstract_purchase> _purchase;
      character::narrative::experience_expense_type _purchase_type;

      static const std::map<character::narrative::experience_expense_type, unsigned int> STANDARD_MULTIPLIER_COST;
    };

  public:
    static experience_cost_inner_computation cost_of(const character::narrative::experience_purchase& purchase);

  };

}


