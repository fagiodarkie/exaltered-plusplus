#ifndef CHARM_PURCHASE_H
#define CHARM_PURCHASE_H

#include "abstract_purchase.h"

namespace character { namespace narrative {

    class charm_purchase : public abstract_purchase
    {
    public:
      charm_purchase();

      virtual void apply(std::shared_ptr<character> c) override;
      virtual void serialisation() override;

      virtual ~charm_purchase() override;

    };
}}
#endif // CHARM_PURCHASE_H
