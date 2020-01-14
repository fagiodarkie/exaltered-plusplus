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
      ability_purchase(ability::detailed_ability ability = ability::MELEE, unsigned int amount = 1);

      ability::detailed_ability ability() const;
      unsigned int amount() const;

      virtual void apply(std::shared_ptr<character::character> c) override;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~ability_purchase() override;

    private:
      ability::detailed_ability _ability;
      unsigned int _amount;

      std::string ability_string() const;
    };

}
#endif // ABILITY_PURCHASE_H
