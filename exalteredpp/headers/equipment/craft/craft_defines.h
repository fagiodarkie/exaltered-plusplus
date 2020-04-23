#ifndef CRAFT_DEFINES_H
#define CRAFT_DEFINES_H

#include <vector>
#include <string>
#include <map>

namespace equipment {

  namespace craft {

    enum class note
    {
      FIREARM,
      MINIMUM
    };

    enum class attack_type
    {
      PUNCH,
      KICK,
      GRAPPLE,
      BASH,
      SLASH,
      THROW,
      FIRE,
      TWO_HAND_BASH,
      TWO_HAND_SLASH,
      SPECIAL,
      DEFAULT
    };

    static const std::vector<attack_type> ATTACK_TYPES = {
      attack_type::PUNCH,
      attack_type::KICK,
      attack_type::GRAPPLE,
      attack_type::BASH,
      attack_type::SLASH,
      attack_type::THROW,
      attack_type::FIRE,
      attack_type::TWO_HAND_BASH,
      attack_type::TWO_HAND_SLASH,
      attack_type::SPECIAL
    };

    static const std::map<attack_type, std::string> ATTACK_TYPE_NAMES = {
      { attack_type::PUNCH,          "Punch" },
      { attack_type::KICK,           "Kick" },
      { attack_type::GRAPPLE,        "Grapple" },
      { attack_type::BASH,           "Bash" },
      { attack_type::SLASH,          "Slash" },
      { attack_type::THROW,          "Throw" },
      { attack_type::FIRE,           "Fire" },
      { attack_type::TWO_HAND_BASH,  "Bash (two hands)" },
      { attack_type::TWO_HAND_SLASH, "Slash (two hands)" },
      { attack_type::SPECIAL,        "Special attack" }
    };
  }
}

#endif // CRAFT_DEFINES_H
