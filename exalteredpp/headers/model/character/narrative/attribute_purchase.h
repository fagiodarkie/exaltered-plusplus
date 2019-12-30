#ifndef ATTRIBUTE_PURCHASE_H
#define ATTRIBUTE_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"
#include "attributes/attribute_names.h"

namespace character { namespace narrative {

    class attribute_purchase : public abstract_purchase, public Serialisable
    {
    public:
      attribute_purchase();

      virtual void apply(std::shared_ptr<character> c) override;

      virtual void serialisation() override;
      virtual std::string description() const = 0;
      virtual std::string key() const = 0;

      virtual ~attribute_purchase() override;

    private:
      unsigned int _amount;
    };

} }
#endif // ATTRIBUTE_PURCHASE_H
