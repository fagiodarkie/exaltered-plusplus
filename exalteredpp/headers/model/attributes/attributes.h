#pragma once

#include <map>
#include "attribute_names.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace attribute
{
  class attributes : public std::map<attribute_enum, int>, public Serialisable
  {

  public:
    virtual void serialisation() override;

    virtual ~attributes() = default;
  };
}

