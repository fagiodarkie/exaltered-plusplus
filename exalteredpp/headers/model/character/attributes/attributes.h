#pragma once

#include <map>
#include "attribute_names.h"
#include "attribute.h"
#include "serialisable.h"

namespace character
{
  class attributes : public std::map<attribute_name, attribute>, serialisable
  {


  public:
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
  };
}

