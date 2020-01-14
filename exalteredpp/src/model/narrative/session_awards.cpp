#include "narrative/session_awards.h"

namespace narrative {

    void session_awards::serialisation()
    {
      if (saving())
        {
          for (auto award_type: AWARD_TYPES)
            if ((*this)[award_type].amount() > 0)
              synch(AWARD_NAME.at(award_type), (*this)[award_type]);
        }
      else
        for (auto award_type: AWARD_TYPES)
          synch(AWARD_NAME.at(award_type), (*this)[award_type]);
    }

}
