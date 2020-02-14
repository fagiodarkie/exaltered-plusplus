#pragma once

#include <QString>

namespace qt {
  namespace labels {
    static QString LOAD_LABEL     = "Load";
    static QString SAVE_LABEL     = "Save";
    static QString NEW_LABEL      = "New";
    static QString NEXT_LABEL     = "Next";
    static QString SUBMIT_LABEL   = "Submit";
    static QString CANCEL_LABEL   = "Cancel";
    static QString APP_TITLE      = "Divine Games";

    namespace info_labels {
      static QString CHARACTER_TYPE_DESCRIPTION(const QString& type, const QString& caste)
      {
        QString result = QString("%0 character").arg(type);
        if (!caste.isEmpty())
          result += QString(" of %0 caste").arg(caste);

        return result;
      }
    }

    namespace exalt_labels {
      static QString CASTE_ABILITIES = "Caste Abilities";
    }

    namespace health_labels {
      static QString HEAL_DAMAGE        = "Heal Damage";
      static QString DEAL_DAMAGE        = "Deal Damage";
      static QString HEAL_CHARACTER     = "Heal %s";
      static QString DAMAGE_CHARACTER   = "Deal Damage to %s";
      static QString CURRENT_HEALTH     = "Current health (over maximum):";
      static QString PENALTY_SUMMARY    = "The damage penalty applies to VDs (external malus) and precision rolls (internal malus).\r\nThey also apply to action duration as additional ticks (in absolute value).";
      static QString HURT_THRESHOLD     = "Hurt threshold (-2)";
      static QString DYING_THRESHOLD    = "Dying threshold (-4):";
      static QString HEAL_DAMAGE_VALUE  = "Health to be restored:";
      static QString DEAL_DAMAGE_VALUE  = "Damage to be dealt:";
    }

    namespace social_labels {
      static QString EMOTIONS_SPECIFIC      = "Emotions";
      static QString COMPULSIONS_SPECIFIC   = "Compulsions";
      static QString ILLUSIONS_SPECIFIC     = "Illusions";
      static QString MOTIVATIONS_SPECIFIC   = "Motivations";
      static QString SERFDOM_SPECIFIC       = "Serfdom";
      static QString PERSONA_VALUE          = "Persona";
      static QString EMOTION_BONUS_VALUE    = "Emotion bonuses";
    }

    namespace essence_labels {
      static QString ESSENCE_TITLE        = "Essence and Logos";
      static QString KHAN                 = "Khan";
      static QString LOGOS                = "Logos";
      static QString CELESTIAL_PORTION    = "Celestial Portion";
      static QString TERRESTRIAL_PORTION  = "Terrestrial Portion";
      static QString PERMANENT_ESSENCE    = "Permanent Essence";
      static QString PERSONAL_ESSENCE     = "Personal Essence";
      static QString PERIPHERAL_ESSENCE   = "Peripheral Essence";
      static QString SPIRITUAL_ESSENCE    = "Spiritual Essence";
      static QString COMMITTED_SUBSCRIPT  = "(Committed)";
    }

    namespace will_virtue_labels {
      static QString WILLPOWER        = "Willpower";
      static QString VIRTUES_SECTION  = "Virtues";
      static QString VIRTUE_TYPE      = "Virtue Type";

      static QString VIRTUE_RANK_DESC(const QString& rank) {
        return QString("(with rank: %0)").arg(rank);
      }
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

      static QString DEFEND_BUTTON = "Defend from Attack";
      static QString ATTACK_BUTTON = "Start Attack";
      static QString SOAK_TEMPLATE = "%1U / %2L / %3A";
    }

    namespace wizards {

      namespace physical_attack {
        static QString WEAPON_PRECISION       = "Weapon Precision:";
        static QString WEAPON_DAMAGE          = "Weapon Damage:";
        static QString WEAPON_DEFENSE         = "Weapon Defense:";
        static QString WEAPON_MIN_DAMAGE      = "Weapon Minimum Damage:";
        static QString WEAPON_DRILL           = "Weapon Drill:"              ;
        static QString WEAPON_ABILITY         = "Weapon Ability:"            ;
        static QString WEAPON_PRECISION_ATTR  = "Weapon Precision Attribute:";
        static QString WEAPON_DAMAGE_ATTR     = "Weapon Damage Attribute:"   ;
        static QString WEAPON_DAMAGE_TYPE     = "Weapon Damage Type:"        ;
        static QString WEAPON_STATS_TITLE     = "Weapon Stats";
        static QString INTERNAL_PRECISION_BONUS = "Internal Precision Bonus:";
        static QString INTERNAL_PRECISION_MALUS = "Internal Precision Malus:";
        static QString EXTERNAL_PRECISION_BONUS = "External Precision Bonus:";
        static QString EXTERNAL_PRECISION_MALUS = "External Precision Malus:";
        static QString BODY_TARGET              = "Targeted body part:";
        static QString ATTACK_STATS_TITLE       = "Attack Stats";

        static QString VD_TYPE              = "VD Type"     ;
        static QString VD_VALUE             = "VD Value"    ;
        static QString NATURAL_SOAK         = "Natural Soak";
        static QString ARMORED_SOAK         = "Armored Soak";
        static QString HARDNESS             = "Hardness"    ;
        static QString DEFENSE_VALUES_TITLE = "Defense Values";
        static QString DEFENSE_ROLL_RECAP_TEMPLATE = "Rolling %0 dice with an external modifier of %1.\r\n"
                                      "Damage type is %2: provide soaks relevant to this damage type.\r\n"
                                      "If the roll passes, the hit will land on the target's %3.";

        static QString BALANCE_RECAP_TEMPLATE = "The defender defended with his %0 vd. What is its balance?";

        static QString KNOCKBACK        = "Knockback";
        static QString KNOCKDOWN        = "Knockdown";
        static QString PUSH_SWITCH      = "Push the defender";
        static QString SPEND_SUCCESSES  = "Spend successes:";
        static QString KNOCK_RECAP = "With a post-soak damage pool of %0 dice, a total of %1 successes were rolled for damage.\r\n"
                                    "Do you wish to spend some to push back or knockdown your opponent?";

        static QString ATTACK_RESULT_MISSED      = "The attack precision was lesser than the chosen VD: the attack was nullified.";
        static QString ATTACK_RESULT_WITH_DAMAGE = "The attack connected with the defender's %0, dealing %1 damage points.";
        static QString ATTACK_RESULT_NO_DAMAGE   = "The attack connected with the defender's %0, but dealt no damage.";
        static QString ATTACK_RESULT_KNOCKDOWN   = "\r\nThe defender was knocked down by the force of the blow!";
        static QString ATTACK_RESULT_KNOCKBACK   = "\r\nThe defender was pushed away %0 meters by the force of the blow!";
        static QString ATTACK_RESULT_COUNTER     = "\r\nThe defender may counter the attack, if he so wishes.";

        static QString DEFENSE_PRECISION_SUMMARY = "Provide the basic information about the attack.";
        static QString PRECISION_ROLL_RESULT     = "Precision roll result:";
        static QString ATTACK_FULL_BASE_DAMAGE   = "Base damage (extra successes excluded):";

        static QString ROLL_DAMAGE_AUTOMATICALLY   = "Roll damage automatically";
        static QString PROVIDE_DAMAGE_ROLL_RESULT  = "Provide the damage roll result";
        static QString ROLLED_DAMAGE_RESULT        = "Provided damage:";
        static QString FINAL_DAMAGE_SUMMARY = "The attacker passed through your defenses with a final damage pool of %0.\r\n"
                              "Are you going to roll that pool automatically or will you provide the result yourself?";


        static QString GOING_TO_COUNTER = "Counter after your parry";
        static QString VD_MODIFIER      = "VD value modifier:";
        static QString DEFENSE_VALUE_RECAP_TEMPLATE = "You're defending with your %0 vd, with a final value of %1.%2";
        static QString COUNTER_SUMMARY              = "\r\nAfter the parry, if successful, you will attempt a counter.";

      }

    }

    namespace creation_wizard {
      static QString CHARACTER_NAME_LABEL = "Character name:";
      static QString CHARACTER_TYPE_LABEL = "Character type:";

      static QString PRIMARY_ATTRIBUTE    = "Primary Attribute";
      static QString SECONDARY_ATTRIBUTE  = "Secondary Attribute";
      static QString TERTIARY_ATTRIBUTE   = "Tertiary Attribute";

      static QString CASTE                = "Caste";
      static QString VICE_SELECTOR        = "Vice";

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
