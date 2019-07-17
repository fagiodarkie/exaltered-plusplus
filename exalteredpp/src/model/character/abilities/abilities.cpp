#include "abilities/abilities.h"
#include "abilities/ability_names.h"

namespace character {

  void abilities::serialisation()
  {
    for (auto ability: ability_names::ABILITIES)
      synch(ability_names::ABILITY_NAME.at(ability), this[ability]);
  }
}
