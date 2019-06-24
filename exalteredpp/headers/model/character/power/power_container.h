#pragma once

#include "willpower.h"
#include "essence.h"
#include "health.h"

namespace character {
  namespace power {
    class power_container
    {
    public:
      power_container();


    private:
      essence     _essence;
      willpower   _willpower;
      health      _health;
    };
  }
}

