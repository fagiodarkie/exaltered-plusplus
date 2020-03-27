#ifndef SPECIALISATION_PURCHASE_H
#define SPECIALISATION_PURCHASE_H

#include "abstract_purchase.h"
#include "../../thirdparty/serialisable/serialisable.hpp"
#include "abilities/ability.h"
#include "abilities/ability_names.h"

namespace narrative {

  class specialisation_purchase : public abstract_purchase, public Serialisable
  {
  public:
    specialisation_purchase(unsigned int amount = 0, ability::ability_name ability = ability::ability_enum::MELEE_LIGHT, const std::string& specialisation = "");

    virtual void apply(std::shared_ptr<character::character> c) override;

    ability::ability_name ability() const;
    std::string specialisation_name() const;
      unsigned int amount() const override;
    virtual void serialisation() override;
    virtual std::string description() const override;
    virtual std::string key() const override;

    virtual ~specialisation_purchase() override;

  private:
    unsigned int _amount;
    ability::ability_name _ability;
    std::string _specialisation;
  };
}
#endif // SPECIALISATION_PURCHASE_H
