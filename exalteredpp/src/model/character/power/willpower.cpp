#include "power/willpower.h"

#include "json_constants.h"

namespace character {
  namespace power {
    willpower::willpower()
      : _permanent_willpower(0), _temporary_willpower(0)
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
      _temporary_willpower -= to_consume;
    }

    void willpower::restore(unsigned int to_restore)
    {
      _temporary_willpower += to_restore;
    }

    unsigned int willpower::permanent_willpower() const
    {
      return _permanent_willpower;
    }

    void willpower::set_permanent_willpower(unsigned int permanent_willpower)
    {
      _permanent_willpower = permanent_willpower;
    }

    void willpower::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_WILLPOWER_TOTAL] = QString::number(_permanent_willpower);
      json[serialisation::json_constants::SLOT_WILLPOWER_TEMP] = QString::number(_temporary_willpower);
    }

    void willpower::read_from_json(const QJsonObject &json)
    {
      _permanent_willpower = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_WILLPOWER_TOTAL].toInt());
      _temporary_willpower = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_WILLPOWER_TEMP].toInt());
    }

    willpower::~willpower() {}

  }
}