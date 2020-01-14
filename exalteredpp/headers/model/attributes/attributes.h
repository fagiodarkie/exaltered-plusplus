#pragma once

#include <map>
#include "attribute_names.h"
#include "attribute.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace attribute
{
  class attributes : public std::map<attribute_enum, attribute>, public Serialisable
  {

  public:
    virtual void serialisation() override;

    virtual ~attributes() = default;
  };
}

