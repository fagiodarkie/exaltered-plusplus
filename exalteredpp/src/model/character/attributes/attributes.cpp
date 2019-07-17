#include "attributes/attributes.h"

namespace character {
  using namespace attribute_names;

  void attributes::serialisation()
  {
    for (auto attribute_type: ATTRIBUTES)
      {
        synch(ATTRIBUTE_NAME.at(attribute_type), this[attribute_type]);
      }
  }

}
