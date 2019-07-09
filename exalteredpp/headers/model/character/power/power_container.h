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

      essence essence() const;
      willpower willpower() const;
      health health() const;
      logos logos() const;

      virtual ~power_container();

    private:
      class essence     _essence;
      class willpower   _willpower;
      class health      _health;
      class logos       _logos;
    };
  }
}

