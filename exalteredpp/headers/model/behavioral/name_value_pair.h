#pragma once

#include <QString>

namespace model {
  class name_value_pair
  {
  public:
    virtual QString get_name() const = 0;
    virtual QString get_value() const = 0;
    virtual ~name_value_pair() = default;
  };

}


