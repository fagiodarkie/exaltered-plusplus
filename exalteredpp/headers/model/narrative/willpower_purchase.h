#ifndef WILLPOWER_PURCHASE_H
#define WILLPOWER_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"

namespace narrative {

    class willpower_purchase : public abstract_purchase, public Serialisable
    {
    public:
      willpower_purchase(unsigned int amount = 1);

      virtual void apply(std::shared_ptr<character::character> c) override;

      unsigned int amount() const override;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~willpower_purchase() override;

    private:
      unsigned int _amount;

    };
}
#endif // WILLPOWER_PURCHASE_H
