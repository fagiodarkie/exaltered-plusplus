#include "equipment/craft/attack_stat_collection.h"

#include "serialisation/json_constants.h"

namespace equipment {
  namespace craft {
    void attack_stat_collection::serialisation()
    {
      if (saving())
        {
          char buffer[3];
          for (auto pair: *this)
            {
              sprintf(buffer, "%d", static_cast<std::underlying_type_t<attack_type>>(pair.first));
              synch(buffer, pair.second);
            }
        }
      else
        {
          for (auto key: objectKeys())
            {
              attack_stat tmp;
              synch(key, tmp);
              attack_type k = static_cast<attack_type>(atoi(key.c_str()));
              (*this)[k] = tmp;
            }
        }
    }
  }
}
