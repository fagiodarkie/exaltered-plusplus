#ifndef ATTRIBUTE_PURCHASE_H
#define ATTRIBUTE_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"
#include "attributes/attribute_names.h"

namespace narrative {

    class attribute_purchase : public abstract_purchase, public Serialisable
    {
    public:
      attribute_purchase(attribute::attribute_enum attribute = attribute::attribute_enum::STRENGTH, unsigned int amount = 1);

      virtual void apply(std::shared_ptr<character::character> c) override;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;
      attribute::attribute_enum attribute() const;
      unsigned int amount() const override;

      virtual ~attribute_purchase() override;

    private:
      unsigned int _amount;
      attribute::attribute_enum _attribute;
    };

}
#endif // ATTRIBUTE_PURCHASE_H
