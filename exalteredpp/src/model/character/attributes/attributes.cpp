#include "attributes/attributes.h"

namespace character {
  using namespace attribute_names;

  void attributes::serialisation()
  {
    for (auto attribute_type: ATTRIBUTES)
      {
        character::attribute& attribute = operator[](attribute_type);
        synch(ATTRIBUTE_NAME.at(attribute_type), attribute);
      }
  }

}
