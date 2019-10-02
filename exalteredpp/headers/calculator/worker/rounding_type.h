#pragma once

#include <cmath>

namespace calculator {

  class round_down {
  public:
    static long int round(const double value)
    {
      return static_cast<long int>(std::floor(value));
    }
  };

  class round_up {
  public:
    static long int round(const double value)
    {
      return static_cast<long int>(std::ceil(value));
    }
  };
}
