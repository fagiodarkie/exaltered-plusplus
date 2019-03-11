#pragma once

#include <map>
#include "attribute_names.h"
#include "attribute.h"

namespace character
{
  class attributes : public std::map<attribute_name, attribute>
  {

  };
}

