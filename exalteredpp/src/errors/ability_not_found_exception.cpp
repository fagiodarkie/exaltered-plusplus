#include "ability_not_found_exception.h"
#include "error_codes.h"

namespace exception {
  const char* ability_not_found_exception::what() const noexcept (true)
  {
    return error_code::character::ABILITY_NOT_FOUND;
  }

  void ability_not_found_exception::raise() const
  {
    throw *this;
  }

  ability_not_found_exception* ability_not_found_exception::clone() const
  {
    return new ability_not_found_exception();
  }
}
