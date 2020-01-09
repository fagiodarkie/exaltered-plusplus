#ifndef SPECIALISATION_PURCHASE_H
#define SPECIALISATION_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"
#include "abilities/ability_names.h"

namespace character { namespace narrative {

    class specialisation_purchase : public abstract_purchase, public Serialisable
    {
    public:
      specialisation_purchase(unsigned int amount = 0, ability_names::ability_enum ability = ability_names::MELEE, const std::string& specialisation = "");

      virtual void apply(std::shared_ptr<character> c) override;

      ability_names::ability_enum ability() const;
      std::string specialisation_name() const;

      virtual void serialisation() override;
      virtual std::string description() const override;
      virtual std::string key() const override;

      virtual ~specialisation_purchase() override;

    private:
      unsigned int _amount;
      ability_names::ability_enum _ability;
      std::string _specialisation;
    };
}}
#endif // SPECIALISATION_PURCHASE_H
