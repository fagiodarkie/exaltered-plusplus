#pragma once

#include <map>
#include "attributeNames.h"
#include "attribute.h"

namespace character {
  class attributes : public std::map<attributeName, attribute>
  {

  };
}

