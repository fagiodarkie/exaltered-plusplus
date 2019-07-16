#pragma once

#include <map>
#include "../thirdparty/serialisable/serialisable.hpp"
#include "ability_names.h"
#include "ability_group.h"

namespace character
{
  class abilities : public std::map<ability_names::ability_enum, ability_group>, public Serialisable
  {

  public:

    virtual void serialisation() override;

    virtual ~abilities() = default;
  };
}
