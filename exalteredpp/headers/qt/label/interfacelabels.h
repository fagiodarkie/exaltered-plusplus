#pragma once

#include <QString>

namespace qt {
  namespace labels {
    static QString LOAD_LABEL     = "Load";
    static QString SAVE_LABEL     = "Save";
    static QString NEW_LABEL      = "New";
    static QString NEXT_LABEL     = "Next";
    static QString CANCEL_LABEL   = "Cancel";
    static QString APP_TITLE      = "Divine Games";

    namespace social_labels {
      static QString EMOTIONS_SPECIFIC      = "Emotions";
      static QString COMPULSIONS_SPECIFIC   = "Compulsions";
      static QString ILLUSIONS_SPECIFIC     = "Illusions";
      static QString MOTIVATIONS_SPECIFIC   = "Motivations";
      static QString SERFDOM_SPECIFIC       = "Serfdom";
      static QString PERSONA_VALUE          = "Persona";
      static QString EMOTION_BONUS_VALUE    = "Emotion bonuses";
    }

    namespace dv_labels {
      static QString PHYS_PARRY_ABILITY = "Physical Parry Ability";
      static QString PHYS_VDS           = "Physical DVs"          ;
      static QString MENTAL_VDS         = "Mental DVs"            ;

      static QString DODGE_DV    = "Dodge DV"      ;
      static QString PARRY_DV    = "Parry DV"      ;
      static QString H_PARRY_DV  = "Heavy Parry DV";
      static QString DODGE_BAL   = "Dodge Balance"      ;
      static QString PARRY_BAL   = "Parry Balance"      ;
      static QString NAT_SOAK    = "Natural Soak"       ;

      static QString M_DODGE_DV         = "Mental Dodge DV"      ;
      static QString M_CHARISMA_PDV     = "Charisma Parry DV"    ;
      static QString M_MANIPULATION_PDV = "Manipulation Parry DV";
      static QString M_APPEARANCE_PDV   = "Appearance Parry DV"  ;
      static QString M_RESILIENCE       = "Social Resilience"    ;
    }

    namespace creation_wizard {
      static QString CHARACTER_NAME_LABEL = "Character name:";
      static QString CHARACTER_TYPE_LABEL = "Character type:";

      static QString PRIMARY_ATTRIBUTE    = "Primary Attribute";
      static QString SECONDARY_ATTRIBUTE  = "Secondary Attribute";
      static QString TERTIARY_ATTRIBUTE   = "Tertiary Attribute";

      static QString CASTE                = "Caste";
      static QString VICE_SELECTOR        = "Vice";

      static QString ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(const QString& label, int points)
      {
        return QString("%1 (total points: %2)").arg(label, QString::number(points));
      }

      static QString ATTRIBUTE_WITH_POINTS(const QString& label, int points)
      {
        return QString("%1: (%2)").arg(label, QString::number(points));
      }
    }
  }
}
