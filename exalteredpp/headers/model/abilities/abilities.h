#pragma once

#include <map>
#include "../thirdparty/serialisable/serialisable.hpp"
#include "ability.h"
#include "ability_group.h"
#include "ability_names.h"

namespace ability
{
  class abilities : public std::map<ability_enum, ability_group>, public Serialisable
  {

  public:

    virtual void serialisation() override;

    virtual ~abilities() = default;
  };
}
