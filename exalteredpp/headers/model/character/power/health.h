#pragma once

#include "serialisable.h"

namespace character {
  namespace power {
    class health : public serialisable
    {
    public:
      health(unsigned int total_health);
      health(unsigned int total_health, unsigned int current_health);

      unsigned int total_health() const;
      unsigned int current_health() const;
      double injured_health_level() const;
      double dying_health_level() const;
      unsigned int current_health_penalty() const;

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~health();
    private:
      unsigned int _total_health, _current_health;

    };
  }
}
