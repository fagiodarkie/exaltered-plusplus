#include "power/health.h"
#include "json_constants.h"

namespace character {
  namespace power {
    health::health(unsigned int total_health)
      : _total_health(total_health), _current_health(total_health)
    { }

    health::health(unsigned int total_health, unsigned int current_health)
      : _total_health(total_health), _current_health(current_health)
    { }


    health::~health() {}

    void health::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_HEALTH_TEMP] = QString::number(_current_health);
      json[serialisation::json_constants::SLOT_HEALTH_TOTAL] = QString::number(_total_health);
    }

    void health::read_from_json(const QJsonObject &json)
    {
      _current_health = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_HEALTH_TEMP].toInt());
      _total_health = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_HEALTH_TOTAL].toInt());
    }

    unsigned int health::total_health() const
    {
      return _total_health;
    }

    unsigned int health::current_health() const
    {
      return _current_health;
    }

    void health::set_total_health(unsigned int total_health)
    {
      _total_health = total_health;
    }

    void health::deal_damage(unsigned int damage)
    {
      _current_health = std::max<unsigned int>(_current_health - damage, 0);
    }

    void health::heal_damage(unsigned int damage)
    {
      _current_health = std::min<unsigned int>(_current_health + damage, _total_health);
    }

    double health::injured_health_level() const
    {
      return _total_health * 0.6;
    }

    double health::dying_health_level() const
    {
      return _total_health * 0.3;
    }

    unsigned int health::current_health_penalty() const
    {
      if (static_cast<double>(_current_health) > injured_health_level())
        return 0;

      if (static_cast<double>(_current_health) > dying_health_level())
        return 2;

      return 4;
    }


  }
}
