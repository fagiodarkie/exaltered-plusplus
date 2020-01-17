#ifndef VIRTUE_PURCHASE_H
#define VIRTUE_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"
#include "virtues/virtue_names.h"

namespace narrative {

    class virtue_purchase : public abstract_purchase, public Serialisable
    {
    public:
      virtue_purchase(unsigned int amount = 1, virtues::virtue_enum virtue = virtues::VALOR);

      virtual void apply(std::shared_ptr<character::character>) override;

      unsigned int amount() const override;
      virtues::virtue_enum virtue() const;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~virtue_purchase() override;

    private:
      unsigned int _amount;
      virtues::virtue_enum _virtue;
    };
}
#endif // VIRTUE_PURCHASE_H
