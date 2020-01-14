#include "abilities/abilities.h"
#include "abilities/ability.h"

namespace ability {

  void abilities::serialisation()
  {
    for (auto ability: ABILITIES)
      synch(ABILITY_NAME.at(ability), operator[](ability));
  }
}
