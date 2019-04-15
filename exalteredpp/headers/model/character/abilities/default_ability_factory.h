#pragma once

#include "abstract_ability_factory.h"

namespace character {
  class default_ability_factory : public abstract_ability_factory
  {
  public:
    default_ability_factory() = default;
    virtual ~default_ability_factory() override = default;

    ability_group get_ability_group(ability_names::ability_name ability) const override;
  };
}
