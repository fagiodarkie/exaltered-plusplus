#include "invalid_parameter.h"

#include "error_codes.h"

namespace exception {

  void invalid_parameter::raise() const
  {
    throw *this;
  }

  const char* invalid_parameter::what() const noexcept (true)
  {
    return error_code::runtime::INVALID_PARAMETER;
  }

  invalid_parameter* invalid_parameter::clone() const
  {
    return new invalid_parameter();
  }
}
