#include "attributes/attributes.h"

namespace attribute {

  void attributes::serialisation()
  {
    for (auto attribute_type: ATTRIBUTES)
      {
        synch(ATTRIBUTE_NAME.at(attribute_type), operator[](attribute_type));
      }
  }

}
