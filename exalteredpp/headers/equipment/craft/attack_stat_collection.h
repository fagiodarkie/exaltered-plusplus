#ifndef ATTACK_STAT_COLLECTION_H
#define ATTACK_STAT_COLLECTION_H

#include "../thirdparty/serialisable/serialisable.hpp"

#include "attack_stat.h"

namespace equipment {
  namespace craft {
    class attack_stat_collection : public Serialisable, public std::map<attack_type, attack_stat>
    {
    public:
      void serialisation() override;
    };
  }
}

#endif // ATTACK_STAT_COLLECTION_H
