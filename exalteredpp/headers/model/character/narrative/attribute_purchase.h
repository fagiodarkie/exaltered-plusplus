#ifndef ATTRIBUTE_PURCHASE_H
#define ATTRIBUTE_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"
#include "attributes/attribute_names.h"

namespace character { namespace narrative {

    class attribute_purchase : public abstract_purchase, public Serialisable
    {
    public:
      attribute_purchase(unsigned int amount = 1, attribute_names::attribute attribute = attribute_names::STRENGTH);

      virtual void apply(std::shared_ptr<character> c) override;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;
      attribute_names::attribute attribute() const;

      virtual ~attribute_purchase() override;

    private:
      unsigned int _amount;
      attribute_names::attribute _attribute;
    };

} }
#endif // ATTRIBUTE_PURCHASE_H
