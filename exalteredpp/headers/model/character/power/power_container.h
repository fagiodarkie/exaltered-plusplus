#pragma once

#include "willpower.h"
#include "essence.h"
#include "health.h"
#include "logos.h"
#include "serialisable.h"

namespace character {
  namespace power {
    class power_container : public serialisable
    {
    public:
      power_container();
      power_container(const essence& essence, const willpower& willpower, const health& health, const logos& logos);

      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;

      essence get_essence() const;
      willpower get_willpower() const;
      health get_health() const;
      logos get_logos() const;

      virtual ~power_container();

    private:
      essence     _essence;
      willpower   _willpower;
      health      _health;
      logos       _logos;
    };
  }
}

