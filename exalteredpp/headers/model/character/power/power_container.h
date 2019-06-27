#pragma once

#include "willpower.h"
#include "essence.h"
#include "health.h"
#include "serialisable.h"


namespace character {
  namespace power {
    class power_container : public serialisable
    {
    public:
      power_container();
      power_container(const essence& essence, const willpower& willpower, const health& health);

    private:
      essence     _essence;
      willpower   _willpower;
      health      _health;

      // serialisable interface
    public:
      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      virtual ~power_container();
    };
  }
}

