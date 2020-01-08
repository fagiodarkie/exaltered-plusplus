#pragma once

#include "abstract_cost_worker.h"

namespace calculator { namespace cost {

    class essence_cost_worker: public abstract_cost_worker
    {
    public:
      virtual unsigned int cost_for(std::shared_ptr<character::character> character) const;

      virtual ~essence_cost_worker() {}

    private:
      static const unsigned int STANDARD_MULTIPLIER = 8;
    };
}
}

