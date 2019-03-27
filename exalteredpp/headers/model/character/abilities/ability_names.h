#pragma once

#include <QMap>
#include <QString>

namespace character
{
  enum ability_name
  {
    MELEE, ARCHERY, THROWN, MARTIAL_ARTS, WAR,
    SURVIVAL, PERFORMANCE, PRESENCE, RESISTANCE, INTEGRITY,
    OCCULT, MEDICINE, INVESTIGATION, KNOWLEDGE, CRAFT,
    STEALTH, AWARENESS, DODGE, ATHLETICS, LARCENY,
    MANEUVER, SOCIALISE, BUREAUCRACY, LANGUAGE
  };

  static const QMap<ability_name, QString> ABILITY_NAME {
    { MELEE,        "Melee" },
    { ARCHERY,      "Archery"},
    { THROWN,       "Thrown"},
    { MARTIAL_ARTS, "Martial Arts"},
    { WAR,          "War"},
    { SURVIVAL,     "Survival"},
    { PERFORMANCE,  "Performance"},
    { PRESENCE,     "Presence"},
    { RESISTANCE,   "Resistance"},
    { INTEGRITY,    "Integrity"},
    { OCCULT,       "Occult"},
    { MEDICINE,     "Medicine"},
    { INVESTIGATION, "Investigation"},
    { KNOWLEDGE,    "Knowledge"},
    { CRAFT,        "Craft"},
    { STEALTH,      "Stealth"},
    { AWARENESS,    "Awareness"},
    { DODGE,        "Dodge"},
    { ATHLETICS,    "Athletics"},
    { LARCENY,      "Larceny"},
    { MANEUVER,     "Maneuver"},
    { SOCIALISE,    "Socialise"},
    { BUREAUCRACY,  "Bureaucracy"},
    { LANGUAGE,     "Language"}
  };
}
