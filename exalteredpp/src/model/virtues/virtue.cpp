#include "virtues/virtue.h"
#include "json_constants.h"
#include "common/reverse_search.h"

namespace virtues {

  using namespace serialisation;

  virtue::virtue(virtue_enum virtue_e, unsigned int value)
    : _virtue_type(virtue_e), _value(value)
  { }

  virtue::virtue(const std::string& serialised_data)
  {
    deserialise(serialised_data);
  }

  virtue_enum virtue::virtue_type() const
  {
    return _virtue_type;
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
    synch(json_constants::SLOT_VALUE, _value);
  }

  virtue::~virtue() {};
}
