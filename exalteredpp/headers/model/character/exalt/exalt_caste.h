#pragma once

#include "abilities/ability_names.h"
#include "creation/character_type_model.h"
#include <QList>

namespace character {
  namespace exalt {

    using character::ability_names::ability;

    enum class caste
    {
      NO_CASTE,
      DAWN, ZENITH, TWILIGHT, NIGHT, ECLIPSE,   // SOLAR
      DUSK, MIDNIGHT, DAYBREAK, DAY, MOONSHADOW,    // ABYSSAL
      SLAYER, MALEFACTOR, DEFILER, SCOURGE, FIEND,  // INFERNAL
      FIRE, WATER, EARTH, AIR, WOOD                 // TERRESTRIAL
    };

    class exalt_caste
    {
    public:
      static exalt_caste get_caste(caste caste_type);

      static QList<ability> _WARRIOR_CASTE,
        _PRIEST_CASTE,
        _SCIENTIST_CASTE,
        _STEALTH_CASTE,
        _DIPLOMAT_CASTE;
      static const QMap<character::creation::character_type, QList<caste>>  CASTES_OF_EXALT_TYPE;
      static const QMap<caste, QString>                                     NAME_OF_CASTE;
      static const QMap<caste, QList<ability>>                              ABILITIES_OF_CASTE;

    private:
      exalt_caste(const QString& caste_name, QList<ability> favorite_abilities);

      QString caste_name;
      QList<character::ability_names::ability> favored_abilities;
    };
  }
}
