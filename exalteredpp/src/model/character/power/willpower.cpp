#include "power/willpower.h"

#include "json_constants.h"

namespace character {
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
      _temporary_willpower -= to_consume > _temporary_willpower ? temporary_willpower() : to_consume;
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

    void willpower::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_WILLPOWER_TOTAL] = QString::number(_permanent_willpower);
      json[serialisation::json_constants::SLOT_WILLPOWER_TEMP] = QString::number(_temporary_willpower);
    }

    void willpower::read_from_json(const QJsonObject &json)
    {
      _permanent_willpower = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_WILLPOWER_TOTAL].toString().toInt());
      _temporary_willpower = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_WILLPOWER_TEMP] .toString().toInt());
    }

    willpower::~willpower() {}

  }
}
