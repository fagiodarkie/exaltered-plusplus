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
      MINIMUM,
      AMMO,
      BUILDINGS,
      DISARMING,
      SPEARLIKE,
      NATURAL,
      LONG,
      EXECUTIONER,
      SINGLE_SHOT,
      SLOW_CHARGE,
      MEDIUM_CHARGE,
      FAST_CHARGE,
      NARRATIVE_CHARGE,
      EMBUED,
      SPLASHING_DAMAGE,
      SHOCK_WAVE,
      INEVITABLE,
      BOOMERANG_EFFECT,
      PUSH
    };

    static const std::vector<note> NOTES = {
      note::FIREARM,
      note::MINIMUM,
      note::AMMO,
      note::BUILDINGS,
      note::DISARMING,
      note::SPEARLIKE,
      note::NATURAL,
      note::LONG,
      note::EXECUTIONER,
      note::SINGLE_SHOT,
      note::SLOW_CHARGE,
      note::MEDIUM_CHARGE,
      note::FAST_CHARGE,
      note::NARRATIVE_CHARGE,
      note::EMBUED,
      note::SPLASHING_DAMAGE,
      note::SHOCK_WAVE,
      note::INEVITABLE,
      note::BOOMERANG_EFFECT,
      note::PUSH
    };

    static const std::map<note, std::string> NOTE_NAME = {
      { note::FIREARM,          "Firearm" },
      { note::MINIMUM,          "Minimum" },
      { note::AMMO,             "Ammunitions" },
      { note::BUILDINGS,        "Siege Weapon" },
      { note::DISARMING,        "Disarming" },
      { note::SPEARLIKE,        "Spear-like" },
      { note::NATURAL,          "Natural Weapon" },
      { note::LONG,             "Long range" },
      { note::EXECUTIONER,      "Executioner Weapon" },
      { note::SINGLE_SHOT,      "Single-Shot" },
      { note::SLOW_CHARGE,      "Recharge (Slow)" },
      { note::MEDIUM_CHARGE,    "Recharge (Medium)" },
      { note::FAST_CHARGE,      "Recharge (Fast)" },
      { note::NARRATIVE_CHARGE, "Recharge (Narrative)" },
      { note::EMBUED,           "Embued Weapon" },
      { note::SPLASHING_DAMAGE, "Splashing Damage" },
      { note::SHOCK_WAVE,       "Shockwave" },
      { note::INEVITABLE,       "Ray" },
      { note::BOOMERANG_EFFECT, "Boomerang Effect" },
      { note::PUSH,             "Push bonus" }
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
