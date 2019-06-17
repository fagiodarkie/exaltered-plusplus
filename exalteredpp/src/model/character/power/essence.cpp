#include "power/essence.h"

namespace character {
  namespace power {

    unsigned int essence::permanent_essence() const
    {
      return _permanent_essence;
    }

    unsigned int essence::khan() const
    {
      return _khan;
    }

    void essence::set_khan(unsigned int khan)
    {
      _khan = khan;
    }

    void essence::set_permanent_essence(unsigned int permanent_essence)
    {
      _permanent_essence = permanent_essence;
    }
  }
}
