#pragma once

#include <QString>

namespace model {
  namespace text {
    namespace character {
      static const std::string DEFAULT_CHARACTER_NAME = "No-namey Mc. Anonymous Face";

    }

    namespace attribute_names {
      static const std::string ATTRIBUTE_CATEGORY_SOCIAL    = "Social"  ;
      static const std::string ATTRIBUTE_CATEGORY_PHYSICAL  = "Physical";
      static const std::string ATTRIBUTE_CATEGORY_MENTAL    = "Mental"  ;

      static const std::string ATTRIBUTE_STRENGTH     = "Strength"    ;
      static const std::string ATTRIBUTE_DEXTERITY    = "Dexterity"   ;
      static const std::string ATTRIBUTE_CONSTITUTION = "Constitution";
      static const std::string ATTRIBUTE_CHARISMA     = "Charisma"    ;
      static const std::string ATTRIBUTE_MANIPULATION = "Manipulation";
      static const std::string ATTRIBUTE_APPEARANCE   = "Appearance"  ;
      static const std::string ATTRIBUTE_INTELLIGENCE = "Intelligence";
      static const std::string ATTRIBUTE_PERCEPTION   = "Perception"  ;
      static const std::string ATTRIBUTE_WITS         = "Wits"        ;
    }

    namespace ability {

      static const std::string ABILITY_CATEGORY_SOCIAL       = "Social"   ;
      static const std::string ABILITY_CATEGORY_COMBAT       = "Combat"   ;
      static const std::string ABILITY_CATEGORY_NARRATIVE    = "Narrative";

      static const std::string ABILITY_MELEE             = "Melee"           ;
      static const std::string ABILITY_ARCHERY           = "Archery"         ;
      static const std::string ABILITY_THROWN            = "Thrown"          ;
      static const std::string ABILITY_MARTIAL_ARTS      = "Martial Arts"    ;
      static const std::string ABILITY_WAR               = "War"             ;
      static const std::string ABILITY_TECHNOLOGY        = "Technology"      ;
      static const std::string ABILITY_PERFORMANCE       = "Performance"     ;
      static const std::string ABILITY_PRESENCE          = "Presence"        ;
      static const std::string ABILITY_RESISTANCE        = "Resistance"      ;
      static const std::string ABILITY_INTEGRITY         = "Integrity"       ;
      static const std::string ABILITY_MEDITATION        = "Meditation"      ;
      static const std::string ABILITY_ACADEMICS         = "Academics"       ;
      static const std::string ABILITY_MEDICINE          = "Medicine"        ;
      static const std::string ABILITY_INVESTIGATION     = "Investigation"   ;
      static const std::string ABILITY_TEACHING          = "Teaching"        ;
      static const std::string ABILITY_CRAFT             = "Craft"           ;
      static const std::string ABILITY_STEALTH           = "Stealth"         ;
      static const std::string ABILITY_AWARENESS         = "Awareness"       ;
      static const std::string ABILITY_DODGE             = "Dodge"           ;
      static const std::string ABILITY_ATHLETICS         = "Athletics"       ;
      static const std::string ABILITY_PRESTIDIGITATION  = "Prestidigitation";
      static const std::string ABILITY_MANEUVER          = "Maneuver"        ;
      static const std::string ABILITY_SOCIALISE         = "Socialise"       ;
      static const std::string ABILITY_BUREAUCRACY       = "Bureaucracy"     ;

    }

    static const std::string WILLPOWER = "Willpower";
    static const std::string ESSENCE = "Essence";
    static const std::string VICE = "Vice";
  }
}
