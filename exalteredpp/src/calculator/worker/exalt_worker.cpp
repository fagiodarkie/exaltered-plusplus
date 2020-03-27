#include "calculator/worker/exalt_worker.h"
#include <algorithm>

namespace calculator {
  namespace worker {

    exalt_worker::~exalt_worker() {}

    double exalt_worker::_lethal_soak              (const character::character& c) const
    {
      return half(c, attribute::attribute_enum::CONSTITUTION);
    }
  }
}
