#pragma once

#include <string>

namespace serialisation
{
  struct json_constants
  {
    static const std::string SLOT_ID;
    static const std::string SLOT_NAME;
    static const std::string SLOT_VALUE;
    static const std::string SLOT_ATTRIBUTES;
    static const std::string SLOT_ABILITIES;
    static const std::string SLOT_SPECIALISATIONS;
    static const std::string SLOT_CASTE;
    static const std::string SLOT_FAVOURITE;
    static const std::string SLOT_RANK;

    static const std::string SLOT_VIRTUES;
    static const std::string SLOT_VICE_ID;
    static const std::string SLOT_VICE_VALUE;

    static const std::string SLOT_WILLPOWER_TOTAL;
    static const std::string SLOT_WILLPOWER_TEMP;
    static const std::string SLOT_HEALTH_TOTAL;
    static const std::string SLOT_HEALTH_TEMP;

    static const std::string SLOT_HEALTH;
    static const std::string SLOT_ESSENCE;
    static const std::string SLOT_WILLPOWER;

    static const std::string SLOT_ESSENCE_PERMANENT;
    static const std::string SLOT_ESSENCE_PERSONAL_TOTAL;
    static const std::string SLOT_ESSENCE_PERSONAL_COMMITTED;
    static const std::string SLOT_ESSENCE_PERSONAL_SPENT;
    static const std::string SLOT_ESSENCE_PERSONAL_BONUS;
    static const std::string SLOT_ESSENCE_PERIPHERAL_TOTAL;
    static const std::string SLOT_ESSENCE_PERIPHERAL_COMMITTED;
    static const std::string SLOT_ESSENCE_PERIPHERAL_SPENT;
    static const std::string SLOT_ESSENCE_PERIPHERAL_BONUS;
    static const std::string SLOT_ESSENCE_SPIRITUAL_TOTAL;
    static const std::string SLOT_ESSENCE_SPIRITUAL_COMMITTED;
    static const std::string SLOT_ESSENCE_SPIRITUAL_SPENT;
    static const std::string SLOT_ESSENCE_SPIRITUAL_BONUS;
    static const std::string SLOT_ESSENCE_KHAN;
    static const std::string SLOT_ESSENCE_CELESTIAL_PORTION;

    static const std::string SLOT_LOGOS;
    static const std::string SLOT_QABBALAH;
    static const std::string SLOT_TOTAL_QABBALAH;
    static const std::string SLOT_ABSOLUTE_PRINCIPLE_CONNECTION;
    static const std::string SLOT_TOTAL_CIRCADIAN_RHYTHM;
    static const std::string SLOT_SPENT_CIRCADIAN_POINTS;

    static const std::string SLOT_PERSONA             ;
    static const std::string SLOT_COMPULSIONS_SPECIFIC;
    static const std::string SLOT_EMOTIONS_SPECIFIC   ;
    static const std::string SLOT_ILLUSIONS_SPECIFIC  ;
    static const std::string SLOT_MOTIVATIONS_SPECIFIC;
    static const std::string SLOT_SERFDOM_SPECIFIC    ;
    static const std::string SLOT_MAX_PHILOSOPHIES    ;
    static const std::string SLOT_MAX_PHILOSOPHY_VALUE;
    static const std::string SLOT_PHILOSOPHIES        ;
    static const std::string SLOT_EMOTION_BONUS       ;

    static const std::string SLOT_CHARACTER_TYPE      ;
    static const std::string SLOT_POWER               ;
  };
}
