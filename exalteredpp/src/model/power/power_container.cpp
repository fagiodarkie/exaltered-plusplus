#include "power/power_container.h"

#include "json_constants.h"

namespace power {
  power_container::power_container()
    : _health(0) {}

  power_container::power_container(const class essence& essence, const class willpower& willpower, const class health& health, const class logos& logos)
    : _essence(essence), _willpower(willpower), _health(health), _logos(logos) { }

  logos power_container::logos() const
  {
    return _logos;
  }

  health power_container::health() const
  {
    return _health;
  }

  willpower power_container::willpower() const
  {
    return _willpower;
  }

  essence power_container::essence() const
  {
    return _essence;
  }

  logos& power_container::logos()
  {
    return _logos;
  }

  health& power_container::health()
  {
    return _health;
  }

  willpower& power_container::willpower()
  {
    return _willpower;
  }

  essence& power_container::essence()
  {
    return _essence;
  }

  power_container::~power_container() {}

  void power_container::serialisation()
  {
    synch(serialisation::json_constants::SLOT_HEALTH   , _health   );
    synch(serialisation::json_constants::SLOT_WILLPOWER, _willpower);
    synch(serialisation::json_constants::SLOT_ESSENCE  , _essence  );
    synch(serialisation::json_constants::SLOT_LOGOS    , _logos    );
  }

}
