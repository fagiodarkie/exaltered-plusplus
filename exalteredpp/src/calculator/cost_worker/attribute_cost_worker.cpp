#include "cost_worker/attribute_cost_worker.h"

#include "narrative/attribute_purchase.h"

namespace calculator { namespace cost {

    unsigned int attribute_cost_worker::cost_for(std::shared_ptr<character::character> character) const
    {
      auto attribute = dynamic_cast<character::narrative::attribute_purchase*>(_purchase.get());

      auto attribute_name = attribute->attribute();

      int current_attribute = character->get_attribute(attribute_name);

      return current_attribute * STANDARD_MULTIPLIER;
    }

}}
