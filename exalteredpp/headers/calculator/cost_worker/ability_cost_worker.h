#pragma once

#include "abstract_cost_worker.h"

namespace calculator { namespace cost {

    class ability_cost_worker: public abstract_cost_worker
    {
    public:
      virtual unsigned int cost_for(std::shared_ptr<character::character> character) const;

      virtual ~ability_cost_worker() {}

    private:
      static const unsigned int FIRST_DOT = 3, STANDARD_MULTIPLIER = 2, FAVORITE_DISCOUNT = 1;
    };
}
}

