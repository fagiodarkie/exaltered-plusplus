#include "virtues/virtue.h"
#include "json_constants.h"
#include "common/reverse_search.h"

namespace character {
  namespace virtues {

    using namespace serialisation;

    virtue::virtue(virtue_enum virtue_e, unsigned int value, virtue_rank rank)
      : _virtue_type(virtue_e), _rank(rank), _value(value)
    { }

    virtue_enum virtue::virtue_type() const
    {
      return _virtue_type;
    }

    virtue_rank virtue::rank() const
    {
      return _rank;
    }

    void virtue::set_rank(virtue_rank rank)
    {
      _rank = rank;
    }

    unsigned int virtue::value() const
    {
      return _value;
    }

    void virtue::set_value(unsigned int value)
    {
      _value = value;
    }

    void virtue::serialisation()
    {
      synch(json_constants::SLOT_NAME , _virtue_type);
      synch(json_constants::SLOT_RANK , _rank);
      synch(json_constants::SLOT_VALUE, _value);
    }

    virtue::~virtue() {};
  }
}
