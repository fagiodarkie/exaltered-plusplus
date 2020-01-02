#include "narrative/session_awards.h"

namespace character { namespace narrative {

    void session_awards::serialisation()
    {
      for (auto award_type: AWARD_TYPES)
        synch(AWARD_NAME.at(award_type), (*this)[award_type]);
    }

} }
