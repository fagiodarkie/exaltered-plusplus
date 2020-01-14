#ifndef ABSTRACT_COST_WORKER_H
#define ABSTRACT_COST_WORKER_H

#include "character.h"

namespace calculator { namespace cost {

    class abstract_cost_worker
    {
    public:

      void with_purchase(std::shared_ptr<narrative::abstract_purchase> purchase)
      {
        _purchase = purchase;
      }

      virtual unsigned int cost_for(std::shared_ptr<character::character> character) const = 0;

      virtual ~abstract_cost_worker() {}

    protected:
      std::shared_ptr<narrative::abstract_purchase> _purchase;
    };
}
}

#endif // ABSTRACT_COST_WORKER_H
