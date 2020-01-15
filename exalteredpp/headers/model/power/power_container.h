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

    essence essence() const;
    willpower willpower() const;
    health health() const;
    logos logos() const;

    class essence& essence();
    class willpower& willpower();
    class health& health();
    class logos& logos();

    virtual void serialisation() override;
    virtual ~power_container();

  private:
    class essence     _essence;
    class willpower   _willpower;
    class health      _health;
    class logos       _logos;
  };
}

