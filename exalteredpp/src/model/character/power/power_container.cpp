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

    void power_container::write_to_json(QJsonObject &json) const
    {
      QJsonObject health_obj,
          essence_obj,
          willpower_obj;

      _health.write_to_json(health_obj);
      _essence.write_to_json(essence_obj);
      _willpower.write_to_json(willpower_obj);

      json[serialisation::json_constants::SLOT_HEALTH]    = health_obj;
      json[serialisation::json_constants::SLOT_WILLPOWER] = willpower_obj;
      json[serialisation::json_constants::SLOT_ESSENCE]   = essence_obj;
    }

    void power_container::read_from_json(const QJsonObject &json)
    {
      _health   .read_from_json(json[serialisation::json_constants::SLOT_HEALTH]   .toObject());
      _willpower.read_from_json(json[serialisation::json_constants::SLOT_WILLPOWER].toObject());
      _essence  .read_from_json(json[serialisation::json_constants::SLOT_ESSENCE]  .toObject());
    }

  }
}
