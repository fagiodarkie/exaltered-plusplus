#include "exalt/exalt_caste.h"

namespace character {
  namespace exalt {

    exalt_caste::exalt_caste(const std::string& caste_name, std::vector<ability::ability_enum> favorite_abilities)
      : caste_name(caste_name), favored_abilities(favorite_abilities)
    {
    }

    exalt_caste exalt_caste::get_caste(caste caste_type)
    {
      return exalt_caste(NAME_OF_CASTE.at(caste_type), ABILITIES_OF_CASTE.at(caste_type));
    }

    std::string exalt_caste::name() const
    {
      return caste_name;
    }

    std::vector<ability_enum> exalt_caste::abilities() const
    {
      return favored_abilities;
    }
  }
}
