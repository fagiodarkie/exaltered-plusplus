#ifndef VICE_PURCHASE_H
#define VICE_PURCHASE_H

#include "abstract_purchase.h"

namespace character { namespace narrative {

    class vice_purchase : public abstract_purchase
    {
    public:
      vice_purchase(unsigned int amount = 1);

      virtual void apply(std::shared_ptr<character>) override;

      unsigned int amount() const;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~vice_purchase() override;

    private:
      unsigned int _amount;
    };
}}
#endif // VICE_PURCHASE_H
