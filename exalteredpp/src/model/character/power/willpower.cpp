#include "power/willpower.h"

namespace character {
  namespace power {
    willpower::willpower()
    {

    }

    unsigned int willpower::temporary_willpower() const
    {
      return _temporary_willpower;
    }

    unsigned int willpower::permanent_willpower() const
    {
      return _permanent_willpower;
    }
  }
}
