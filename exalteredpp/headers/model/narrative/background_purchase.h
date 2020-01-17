#ifndef BACKGROUND_PURCHASE_H
#define BACKGROUND_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"

namespace narrative {

    class background_purchase : public abstract_purchase, public Serialisable
    {
    public:
      background_purchase();

      virtual void apply(std::shared_ptr<character::character>) override;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;
      virtual unsigned int amount() const override;

      virtual ~background_purchase() override;

    private:
      unsigned int _amount;
    };
  }
#endif // BACKGROUND_PURCHASE_H
