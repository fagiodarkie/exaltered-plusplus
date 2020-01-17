#ifndef ESSENCE_PURCHASE_H
#define ESSENCE_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"

namespace narrative {

    class essence_purchase : public abstract_purchase, public Serialisable
    {
    public:
      essence_purchase(unsigned int amount = 1);
      unsigned int amount() const override;
      virtual void apply(std::shared_ptr<character::character> c) override;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~essence_purchase() override;

    private:
      unsigned int _amount;

    };

}
#endif // ESSENCE_PURCHASE_H
