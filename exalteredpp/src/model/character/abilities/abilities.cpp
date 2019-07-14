#include "abilities/abilities.h"
#include "abilities/ability_names.h"

namespace character {

  void abilities::serialisation()
  {
    for (auto ability: *this)
      synch(ability_names::ABILITY_NAME[ability.first], ability.second);
  }
}
