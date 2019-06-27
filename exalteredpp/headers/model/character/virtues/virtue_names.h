#include <QMap>

#pragma once

namespace character {
  namespace virtues {
    enum virtue_enum {
      COMPASSION, VALOR, CONVINCTION, TEMPERANCE
    };

    enum vice_enum {
      LUST = 1, GLUTTONY, WRATH, SLOTH, PRIDE, ENVY, GREED
    };

    enum virtue_rank {
      CHILD, TEENAGER, ADULT, SENIOR
    };

    static const QList<virtue_enum> VIRTUE_LIST = {
      COMPASSION, CONVINCTION, VALOR, TEMPERANCE
    };

    static const QList<vice_enum> VICE_LIST = {
      LUST, GLUTTONY, WRATH, SLOTH, PRIDE, ENVY, GREED
    };

    static const QList<virtue_rank> VIRTUE_RANK_LIST = {
      CHILD, TEENAGER, ADULT, SENIOR
    };

    static const QMap<virtue_enum, QString> VIRTUE_NAME = {
      { COMPASSION,     "Compassion"    },
      { CONVINCTION,    "Convinction"   },
      { VALOR,          "Valor"         },
      { TEMPERANCE,     "Temperance"    }
    };

    static const QMap<vice_enum, QString> VICE_NAME = {
      { LUST,     "Lust"      },
      { GLUTTONY, "Gluttony"  },
      { WRATH,    "Wrath"     },
      { SLOTH,    "Sloth"     },
      { PRIDE,    "Pride"     },
      { ENVY,     "Envy"      },
      { GREED,    "Greed"     }
    };

    static const QMap<virtue_rank, QString> RANK_NAME = {
      { CHILD,    "Child"   },
      { TEENAGER, "Teenager"},
      { ADULT,    "Adult"   },
      { SENIOR,   "Senior"  }
    };

  }
}
