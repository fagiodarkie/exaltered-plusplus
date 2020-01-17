#include "power/health.h"
#include "json_constants.h"
#include <algorithm>

namespace power {
  health::health(unsigned int total_health)
    : _total_health(total_health), _current_health(total_health)
  { }

  health::health(unsigned int total_health, unsigned int current_health)
    : _total_health(total_health), _current_health(current_health)
  { }


  health::~health() {}

  void health::serialisation()
  {
    synch(serialisation::json_constants::SLOT_HEALTH_TEMP, _current_health);
    synch(serialisation::json_constants::SLOT_HEALTH_TOTAL, _total_health);
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
    _current_health = _current_health > damage ? _current_health - damage : 0;
  }

  void health::heal_damage(unsigned int damage)
  {
    _current_health = std::min(_current_health + damage, _total_health);
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
