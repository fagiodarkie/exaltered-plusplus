#include "power/power_container.h"

#include "json_constants.h"

namespace character {
  namespace power {
    power_container::power_container()
      : _health(0) {}

    power_container::power_container(const essence& essence, const willpower& willpower, const health& health)
      : _essence(essence), _willpower(willpower), _health(health) { }


    power_container::~power_container() {}

    void power_container::write_to_json(QJsonObject &json) const
    {
      QJsonObject health_obj,
          essence_obj,
          willpower_obj;

      _health.write_to_json(health_obj);
      _essence.write_to_json(essence_obj);
      _willpower.write_to_json(willpower_obj);

      json[serialisation::json_constants::SLOT_HEALTH] = health_obj;
      json[serialisation::json_constants::SLOT_WILLPOWER] = willpower_obj;
      json[serialisation::json_constants::SLOT_ESSENCE] = essence_obj;
    }
  }
}
