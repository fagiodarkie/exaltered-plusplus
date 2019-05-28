#include "exalt/exalt_caste.h"

namespace character {
  namespace exalt {

    exalt_caste::exalt_caste(const QString& caste_name, QList<character::ability_names::ability> favorite_abilities)
      : caste_name(caste_name), favored_abilities(favorite_abilities)
    {

    }

  }
}
