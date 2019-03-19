#include "characternotfoundexception.h"

#include "error_codes.h"

namespace exception {

  void character_not_found_exception::raise() const
  {
    throw *this;
  }

  const char* character_not_found_exception::what() const noexcept (true)
  {
    return error_code::serialisation::CHARACTER_NOT_FOUND;
  }

  character_not_found_exception* character_not_found_exception::clone() const
  {
    return new character_not_found_exception();
  }
}
