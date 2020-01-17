#include "cost_worker/attribute_cost_worker.h"

#include "narrative/attribute_purchase.h"

namespace calculator { namespace cost {

    unsigned int attribute_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      auto attribute = dynamic_cast<narrative::attribute_purchase*>(_purchase.get());

      auto attribute_name = attribute->attribute();

      int current_attribute = character->attribute(attribute_name);

      unsigned int result = 0;
      for (int value = current_attribute; value < _purchase->amount(); ++value)
        result += value * STANDARD_MULTIPLIER;
      return result;
    }

}}
