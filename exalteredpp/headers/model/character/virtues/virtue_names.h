#pragma once

#include <map>
#include <list>

namespace character {
  namespace virtues {
    enum virtue_enum {
      COMPASSION = 0, VALOR, CONVINCTION, TEMPERANCE
    };

    enum vice_enum {
      LUST = 0, GLUTTONY, WRATH, SLOTH, PRIDE, ENVY, GREED
    };

    enum virtue_rank {
      CHILD = 0, TEENAGER, ADULT, SENIOR
    };

    static const std::list<virtue_enum> VIRTUE_LIST = {
      COMPASSION, CONVINCTION, VALOR, TEMPERANCE
    };

    static const std::list<vice_enum> VICE_LIST = {
      LUST, GLUTTONY, WRATH, SLOTH, PRIDE, ENVY, GREED
    };

    static const std::list<virtue_rank> VIRTUE_RANK_LIST = {
      CHILD, TEENAGER, ADULT, SENIOR
    };

    static const std::map<virtue_enum, std::string> VIRTUE_NAME = {
      { COMPASSION,     "Compassion"    },
      { CONVINCTION,    "Convinction"   },
      { VALOR,          "Valor"         },
      { TEMPERANCE,     "Temperance"    }
    };

    static const std::map<vice_enum, std::string> VICE_NAME = {
      { LUST,     "Lust"      },
      { GLUTTONY, "Gluttony"  },
      { WRATH,    "Wrath"     },
      { SLOTH,    "Sloth"     },
      { PRIDE,    "Pride"     },
      { ENVY,     "Envy"      },
      { GREED,    "Greed"     }
    };

    static const std::map<virtue_rank, std::string> RANK_NAME = {
      { CHILD,    "Child"   },
      { TEENAGER, "Teenager"},
      { ADULT,    "Adult"   },
      { SENIOR,   "Senior"  }
    };

  }
}
