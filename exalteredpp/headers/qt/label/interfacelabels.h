#pragma once

#include <QString>

namespace qt {
  namespace labels {

    static const QString PARTIAL_OVER_TOTAL(int partial, int total) {
      return QString("%1 / %2").arg(partial).arg(total);
    }

    static const QString LOAD_LABEL     = "Load";
    static const QString SAVE_LABEL     = "Save";
    static const QString NEW_LABEL      = "New";
    static const QString NEXT_LABEL     = "Next";
    static const QString SUBMIT_LABEL   = "Submit";
    static const QString CANCEL_LABEL   = "Cancel";
    static const QString APP_TITLE      = "Divine Games";
    static const QString BACK_LABEL     = "Back";
    static const QString EDIT_LABEL     = "Edit";
    static const QString BACK_TO_MENU_LABEL = "Back to menu";

    namespace info_labels {
      static const QString CHARACTER_TYPE_DESCRIPTION(const QString& type, const QString& caste)
      {
        QString result = QString("%0 character").arg(type);
        if (!caste.isEmpty())
          result += QString(" of %0 caste").arg(caste);

        return result;
      }
    }

    namespace exalt_labels {
      static const QString CASTE_ABILITIES = "Caste Abilities";
    }

    namespace health_labels {
      static const QString HEAL_DAMAGE        = "Heal Damage";
      static const QString DEAL_DAMAGE        = "Deal Damage";
      static const QString HEAL_CHARACTER     = "Heal %1";
      static const QString DAMAGE_CHARACTER   = "Deal Damage to %1";
      static const QString CURRENT_HEALTH     = "Current health:";
      static const QString PENALTY_SUMMARY    = "The damage penalty applies to VDs (external malus) and precision rolls (internal malus).\r\nThey also apply to action duration as additional ticks (in absolute value).";
      static const QString HURT_THRESHOLD     = "Hurt threshold (-2):";
      static const QString DYING_THRESHOLD    = "Dying threshold (-4):";
      static const QString HEAL_DAMAGE_VALUE  = "Health to be restored:";
      static const QString DEAL_DAMAGE_VALUE  = "Damage to be dealt:";
      static const QString HEALTH_TITLE       = "Health summary";
    }

    namespace social_labels {
      static const QString EMOTIONS_SPECIFIC      = "Emotions";
      static const QString COMPULSIONS_SPECIFIC   = "Compulsions";
      static const QString ILLUSIONS_SPECIFIC     = "Illusions";
      static const QString MOTIVATIONS_SPECIFIC   = "Motivations";
      static const QString SERFDOM_SPECIFIC       = "Serfdom";
      static const QString PERSONA_VALUE          = "Persona";
      static const QString EMOTION_BONUS_VALUE    = "Emotion bonuses";
    }

    namespace essence_labels {
      static const QString ESSENCE_TITLE        = "Essence and Logos";
      static const QString KHAN                 = "Khan";
      static const QString LOGOS                = "Logos";
      static const QString CELESTIAL_PORTION    = "Celestial Portion";
      static const QString TERRESTRIAL_PORTION  = "Terrestrial Portion";
      static const QString PERMANENT_ESSENCE    = "Permanent Essence";
      static const QString PERSONAL_ESSENCE     = "Personal Essence";
      static const QString PERIPHERAL_ESSENCE   = "Peripheral Essence";
      static const QString SPIRITUAL_ESSENCE    = "Spiritual Essence";
      static const QString COMMITTED_SUBSCRIPT  = "(Committed)";
    }

    namespace will_virtue_labels {
      static const QString WILLPOWER        = "Willpower";
      static const QString VIRTUES_SECTION  = "Virtues";
      static const QString VIRTUE_TYPE      = "Virtue Type";

      static const QString VIRTUE_RANK_DESC(const QString& rank) {
        return QString("(with rank: %0)").arg(rank);
      }
    }

    namespace dv_labels {
      static const QString PHYS_PARRY_ABILITY = "Physical Parry Ability";
      static const QString PHYS_VDS           = "Physical DVs"          ;
      static const QString MENTAL_VDS         = "Mental DVs"            ;

      static const QString DODGE_DV    = "Dodge DV"      ;
      static const QString PARRY_DV    = "Parry DV"      ;
      static const QString H_PARRY_DV  = "Heavy Parry DV";
      static const QString DODGE_BAL   = "Dodge Balance"      ;
      static const QString PARRY_BAL   = "Parry Balance"      ;
      static const QString NAT_SOAK    = "Natural Soak"       ;

      static const QString M_DODGE_DV         = "Mental Dodge DV"      ;
      static const QString M_CHARISMA_PDV     = "Charisma Parry DV"    ;
      static const QString M_MANIPULATION_PDV = "Manipulation Parry DV";
      static const QString M_APPEARANCE_PDV   = "Appearance Parry DV"  ;
      static const QString M_RESILIENCE       = "Social Resilience"    ;

      static const QString DEFEND_BUTTON = "Defend from Attack";
      static const QString ATTACK_BUTTON = "Start Attack";
      static const QString SOAK_TEMPLATE = "%1U / %2L / %3A";
    }

    namespace wizards {

      namespace physical_attack {
        static const QString WEAPON_PRECISION       = "Weapon Precision:";
        static const QString WEAPON_CADENCE         = "Weapon Cadence:";
        static const QString WEAPON_ENCUMBRANCE     = "Weapon Encumbrance:";
        static const QString WEAPON_HINDRANCE       = "Weapon Hindrance:";
        static const QString WEAPON_BULK            = "Weapon Bulk:";
        static const QString WEAPON_DAMAGE          = "Weapon Damage:";
        static const QString WEAPON_DEFENSE         = "Weapon Defense:";
        static const QString WEAPON_RANGE           = "Weapon Range:";
        static const QString WEAPON_MIN_DAMAGE      = "Weapon Minimum Damage:";
        static const QString WEAPON_DRILL           = "Weapon Drill:"              ;
        static const QString WEAPON_ABILITY         = "Weapon Ability:"            ;
        static const QString WEAPON_PRECISION_ATTR  = "Weapon Precision Attribute:";
        static const QString WEAPON_DAMAGE_ATTR     = "Weapon Damage Attribute:"   ;
        static const QString WEAPON_DAMAGE_TYPE     = "Weapon Damage Type:"        ;
        static const QString WEAPON_STATS_TITLE     = "Weapon Stats";
        static const QString INTERNAL_PRECISION_BONUS = "Internal Precision Bonus:";
        static const QString INTERNAL_PRECISION_MALUS = "Internal Precision Malus:";
        static const QString EXTERNAL_PRECISION_BONUS = "External Precision Bonus:";
        static const QString EXTERNAL_PRECISION_MALUS = "External Precision Malus:";
        static const QString BODY_TARGET              = "Targeted body part:";
        static const QString ATTACK_STATS_TITLE       = "Attack Stats";
        static const QString NOTES_TITLE              = "Notes";

        static const QString VD_TYPE              = "VD Type"     ;
        static const QString VD_VALUE             = "VD Value"    ;
        static const QString NATURAL_SOAK         = "Natural Soak";
        static const QString ARMORED_SOAK         = "Armored Soak";
        static const QString HARDNESS             = "Hardness"    ;
        static const QString DEFENSE_VALUES_TITLE = "Defense Values";
        static const QString DEFENSE_ROLL_RECAP_TEMPLATE = "Rolling %0 dice with an external modifier of %1.\r\n"
                                      "Damage type is %2: provide soaks relevant to this damage type.\r\n"
                                      "If the roll passes, the hit will land on the target's %3.";

        static const QString BALANCE_RECAP_TEMPLATE = "The defender defended with his %0 vd. What is its balance?";

        static const QString KNOCKBACK        = "Knockback";
        static const QString KNOCKDOWN        = "Knockdown";
        static const QString PUSH_SWITCH      = "Push the defender";
        static const QString SPEND_SUCCESSES  = "Spend successes:";
        static const QString KNOCK_RECAP = "With a post-soak damage pool of %0 dice, a total of %1 successes were rolled for damage.\r\n"
                                    "Do you wish to spend some to push back or knockdown your opponent?";

        static const QString ATTACK_RESULT_MISSED      = "The attack precision was lesser than the chosen VD: the attack was nullified.";
        static const QString ATTACK_RESULT_WITH_DAMAGE = "The attack connected with the defender's %0, dealing %1 damage points.";
        static const QString ATTACK_RESULT_NO_DAMAGE   = "The attack connected with the defender's %0, but dealt no damage.";
        static const QString ATTACK_RESULT_KNOCKDOWN   = "\r\nThe defender was knocked down by the force of the blow!";
        static const QString ATTACK_RESULT_KNOCKBACK   = "\r\nThe defender was pushed away %0 meters by the force of the blow!";
        static const QString ATTACK_RESULT_COUNTER     = "\r\nThe defender may counter the attack, if he so wishes.";

        static const QString DEFENSE_PRECISION_SUMMARY = "Provide the basic information about the attack.";
        static const QString PRECISION_ROLL_RESULT     = "Precision roll result:";
        static const QString ATTACK_FULL_BASE_DAMAGE   = "Base damage (extra successes excluded):";

        static const QString ROLL_DAMAGE_AUTOMATICALLY   = "Roll damage automatically";
        static const QString PROVIDE_DAMAGE_ROLL_RESULT  = "Provide the damage roll result";
        static const QString ROLLED_DAMAGE_RESULT        = "Provided damage:";
        static const QString FINAL_DAMAGE_SUMMARY = "The attacker passed through your defenses with a final damage pool of %0.\r\n"
                              "Are you going to roll that pool automatically or will you provide the result yourself?";


        static const QString GOING_TO_COUNTER = "Counter after your parry";
        static const QString VD_MODIFIER      = "VD value modifier:";
        static const QString DEFENSE_VALUE_RECAP_TEMPLATE = "You're defending with your %0 vd, with a final value of %1.%2";
        static const QString COUNTER_SUMMARY              = "\r\nAfter the parry, if successful, you will attempt a counter.";

      }

    }

    namespace craft_wizard {
      static const QString PROJECT_FINISHED   = "Submit project";
      static const QString ATTACKS_CHOSEN     = "Attacks chosen";
      static const QString PROJECT_NAME       = "Project name";
      static const QString ATTACKS            = "Attacks";
      static const QString DEFAULT_ATTACK     = "Default attack:";
      static const QString STATS              = "General stats";
      static const QString HEAVY_WEAPON_CHECK = "Heavy weapon";
      static const QString MINIMUMS_GROUP     = "Minimums";
    }

    namespace creation_wizard {
      static const QString CHARACTER_NAME_LABEL = "Character name:";
      static const QString CHARACTER_TYPE_LABEL = "Character type:";

      static const QString PRIMARY_ATTRIBUTE    = "Primary Attribute";
      static const QString SECONDARY_ATTRIBUTE  = "Secondary Attribute";
      static const QString TERTIARY_ATTRIBUTE   = "Tertiary Attribute";

      static const QString CASTE                = "Caste";
      static const QString VICE_SELECTOR        = "Vice";

      static QString ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(const QString& label, int current_points, int total_points)
      {
        return QString("%1 (%2 / %3)").arg(label, QString::number(current_points), QString::number(total_points));
      }

      static QString ATTRIBUTE_LABEL_WITH_TOTAL_POINTS(const QString& label, int total_points)
      {
        return QString("%1 (total points: %2)").arg(label, QString::number(total_points));
      }

      static QString ATTRIBUTE_WITH_POINTS(const QString& label, int points)
      {
        return QString("%1: (%2)").arg(label, QString::number(points));
      }
    }

    static QString AVAILABLE_OVER_TOTAL(int available, int total)
    {
      return QString("%1 / %2").arg(available).arg(total);
    }

    static QString SPECIFY_SUBLABEL(const QString& general, const QString& specific)
    {
      return QString("%1 (%2)").arg(general).arg(specific);
    }
  }
}
