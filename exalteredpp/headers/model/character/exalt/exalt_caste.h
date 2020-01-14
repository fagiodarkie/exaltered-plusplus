#pragma once

#include "abilities/ability.h"
#include "creation/character_type_model.h"
#include "abilities/ability_names.h"
#include <vector>

namespace character {
  namespace exalt {

    using ability::ability_enum;

    enum class caste
    {
      NO_CASTE = 0,
      DAWN, ZENITH, TWILIGHT, NIGHT, ECLIPSE,       // SOLAR
      DUSK, MIDNIGHT, DAYBREAK, DAY, MOONSHADOW,    // ABYSSAL
      SLAYER, MALEFACTOR, DEFILER, SCOURGE, FIEND,  // INFERNAL
      FIRE, WATER, EARTH, AIR, WOOD                 // TERRESTRIAL
    };

    static const std::vector<caste> CASTES = {
      caste::NO_CASTE,
      caste::DAWN, caste::ZENITH, caste::TWILIGHT, caste::NIGHT, caste::ECLIPSE,
      caste::DUSK, caste::MIDNIGHT, caste::DAYBREAK, caste::DAY, caste::MOONSHADOW,
      caste::SLAYER, caste::MALEFACTOR, caste::DEFILER, caste::SCOURGE, caste::FIEND,
      caste::FIRE, caste::WATER, caste::EARTH, caste::AIR, caste::WOOD
    };

    class exalt_caste
    {
    public:
      static exalt_caste get_caste(caste caste_type);

      static const std::map<creation::character_type, std::vector<caste>>  CASTES_OF_EXALT_TYPE;
      static const std::map<caste, std::string>                                     NAME_OF_CASTE;

      std::string name() const;
      std::vector<ability_enum> abilities() const;

    private:
      static std::vector<ability_enum> _WARRIOR_CASTE,
        _PRIEST_CASTE,
        _SCIENTIST_CASTE,
        _STEALTH_CASTE,
        _DIPLOMAT_CASTE;

      static const std::map<caste, std::vector<ability_enum>>                         ABILITIES_OF_CASTE;

      exalt_caste(const std::string& caste_name, std::vector<ability_enum> favorite_abilities);

      std::string caste_name;
      std::vector<ability::ability_enum> favored_abilities;
    };
  }
}
