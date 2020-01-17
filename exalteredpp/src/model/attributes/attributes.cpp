#include "attributes/attributes.h"

namespace attribute {

  void attributes::serialisation()
  {
    for (auto attributeype: ATTRIBUTES)
      {
        synch(ATTRIBUTE_NAME.at(attributeype), operator[](attributeype));
      }
  }

}
