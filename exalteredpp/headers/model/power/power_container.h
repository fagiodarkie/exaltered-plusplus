#pragma once

#include "willpower.h"
#include "essence.h"
#include "health.h"
#include "logos.h"
#include "../thirdparty/serialisable/serialisable.hpp"

namespace power {
  class power_container : public Serialisable
  {
  public:
    power_container();
    power_container(const essence& essence, const willpower& willpower, const health& health, const logos& logos);

    essence get_essence() const;
    willpower get_willpower() const;
    health get_health() const;
    logos get_logos() const;

    essence& get_essence();
    willpower& get_willpower();
    health& get_health();
    logos& get_logos();

    virtual void serialisation() override;
    virtual ~power_container();

  private:
    essence     _essence;
    willpower   _willpower;
    health      _health;
    logos       _logos;
  };
}

