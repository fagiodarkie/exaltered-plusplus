#include "power/power_container.h"

#include "json_constants.h"

namespace character {
  namespace power {
    power_container::power_container()
      : _health(0) {}

    power_container::power_container(const essence& essence, const willpower& willpower, const health& health, const logos& logos)
      : _essence(essence), _willpower(willpower), _health(health), _logos(logos) { }

    logos power_container::get_logos() const
    {
      return _logos;
    }

    health power_container::get_health() const
    {
      return _health;
    }

    willpower power_container::get_willpower() const
    {
      return _willpower;
    }

    essence power_container::get_essence() const
    {
      return _essence;
    }

    power_container::~power_container() {}

    void power_container::serialisation()
    {
      synch(serialisation::json_constants::SLOT_HEALTH   , _health   );
      synch(serialisation::json_constants::SLOT_WILLPOWER, _willpower);
      synch(serialisation::json_constants::SLOT_ESSENCE  , _essence  );
    }

  }
}
