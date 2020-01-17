#ifndef CHARM_PURCHASE_H
#define CHARM_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"

namespace narrative {

    class charm_purchase : public abstract_purchase, public Serialisable
    {
    public:
      charm_purchase();

      virtual void apply(std::shared_ptr<character::character> c) override;
      virtual void serialisation() override;
      virtual unsigned int amount() const override;

      virtual ~charm_purchase() override;

    };
}
#endif // CHARM_PURCHASE_H
