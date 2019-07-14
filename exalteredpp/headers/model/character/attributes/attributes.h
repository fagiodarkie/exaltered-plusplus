#pragma once

#include <map>
#include "attribute_names.h"
#include "attribute.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace character
{
  class attributes : public std::map<attribute_names::attribute, attribute>, Serialisable
  {

  public:
    virtual void serialisation() override;

    virtual ~attributes() = default;
  };
}

