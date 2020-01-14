#include "power/willpower.h"
#include <algorithm>
#include "json_constants.h"

namespace power {
  willpower::willpower(unsigned int total, unsigned int temporary)
    : _permanent_willpower(total), _temporary_willpower(temporary)
  { }

  unsigned int willpower::temporary_willpower() const
  {
    return _temporary_willpower;
  }

  bool willpower::can_consume(unsigned int to_consume) const
  {
    return _temporary_willpower >= to_consume;
  }

  void willpower::consume(unsigned int to_consume)
  {
    _temporary_willpower -= (to_consume > _temporary_willpower ? temporary_willpower() : to_consume);
  }

  void willpower::restore(unsigned int to_restore)
  {
    _temporary_willpower = std::min(_temporary_willpower + to_restore, _permanent_willpower);
  }

  unsigned int willpower::permanent_willpower() const
  {
    return _permanent_willpower;
  }

  void willpower::set_permanent_willpower(unsigned int permanent_willpower)
  {
    _permanent_willpower = permanent_willpower;
  }

  void willpower::serialisation()
  {
    synch(serialisation::json_constants::SLOT_WILLPOWER_TOTAL, _permanent_willpower);
    synch(serialisation::json_constants::SLOT_WILLPOWER_TEMP,  _temporary_willpower);
  }

  willpower::~willpower() {}

}

