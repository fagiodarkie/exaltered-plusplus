#pragma once

#include <string>

namespace model {
  class name_value_pair
  {
  public:
    virtual std::string get_name() const = 0;
    virtual std::string get_value() const = 0;
    virtual ~name_value_pair() = default;
  };

}


