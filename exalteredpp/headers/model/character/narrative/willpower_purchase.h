#ifndef WILLPOWER_PURCHASE_H
#define WILLPOWER_PURCHASE_H

#include "abstract_purchase.h"

namespace character { namespace narrative {

    class willpower_purchase : public abstract_purchase
    {
    public:
      willpower_purchase(unsigned int amount = 1);

      virtual void apply(std::shared_ptr<character> c) override;

      unsigned int amount() const;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~willpower_purchase() override;

    private:
      unsigned int _amount;

    };
}}
#endif // WILLPOWER_PURCHASE_H
