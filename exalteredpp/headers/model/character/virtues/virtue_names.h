#include <QMap>

#pragma once

namespace character {
  namespace virtues {
    enum virtue_enum {
      COMPASSION, VALOR, CONVINCTION, TEMPERANCE
    };

    enum vice_enum {
      LUST, GLUTTONY, WRATH, SLOTH, PRIDE, ENVY, GREED
    };

    static QMap<virtue_enum, QString> VIRTUE_NAME = {
      { COMPASSION,     "Compassion"    },
      { CONVINCTION,    "Convinction"   },
      { VALOR,          "Valor"         },
      { TEMPERANCE,     "Temperance"    }
    };
  }
}
