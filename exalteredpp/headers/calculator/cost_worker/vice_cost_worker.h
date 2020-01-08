#ifndef VICE_COST_WORKER_H
#define VICE_COST_WORKER_H

#include "abstract_cost_worker.h"

namespace calculator { namespace cost {

    class vice_cost_worker: public abstract_cost_worker
    {
    public:
      virtual unsigned int cost_for(std::shared_ptr<character::character> character) const;

      virtual ~vice_cost_worker() {}

    private:
      static const unsigned int STANDARD_MULTIPLIER = 3;
    };
}
}
#endif // VICE_COST_WORKER_H
