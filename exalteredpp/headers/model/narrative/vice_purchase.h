#ifndef VICE_PURCHASE_H
#define VICE_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"

namespace narrative {

    class vice_purchase : public abstract_purchase, public Serialisable
    {
    public:
      vice_purchase(unsigned int amount = 1);

      virtual void apply(std::shared_ptr<character::character>) override;

      unsigned int amount() const override;
      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~vice_purchase() override;

    private:
      unsigned int _amount;
    };
}
#endif // VICE_PURCHASE_H
