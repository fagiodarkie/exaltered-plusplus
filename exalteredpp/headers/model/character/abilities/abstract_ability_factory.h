#pragma once

#include "ability_names.h"
#include "ability_group.h"

namespace character {

  class abstract_ability_factory
  {
  public:
    virtual ability_group get_ability_group(ability_names::ability ability) const = 0;
    virtual ~abstract_ability_factory() = default;
  };

}
