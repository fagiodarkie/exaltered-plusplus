#ifndef ABILITY_PURCHASE_H
#define ABILITY_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"
#include "abilities/ability.h"
#include "abilities/ability_names.h"

namespace narrative {

    class ability_purchase : public abstract_purchase, public Serialisable
    {
    public:
      ability_purchase(ability::ability_name ability = ability::ability_enum::MELEE_LIGHT, unsigned int amount = 1);

      ability::ability_name ability() const;
      unsigned int amount() const override;
      virtual void apply(std::shared_ptr<character::character> c) override;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~ability_purchase() override;

    private:
      ability::ability_name _ability;
      unsigned int _amount;
    };

}
#endif // ABILITY_PURCHASE_H
