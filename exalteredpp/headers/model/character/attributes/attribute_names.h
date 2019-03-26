#pragma once

#include <QMap>
#include <QString>

namespace character
{
  enum attribute_name
  {
    STRENGTH, DEXTERITY, CONSTITUTION,
    CHARISMA, MANIPULATION, APPEARANCE,
    INTELLIGENCE, PERCEPTION, WITS
  };

  static const QMap<attribute_name, QString> ATTRIBUTE_NAME {
    { STRENGTH,     "Strength" },
    { DEXTERITY,    "Dexterity" },
    { CONSTITUTION, "Constitution" },
    { CHARISMA,     "Charisma" },
    { MANIPULATION, "Manipulation" },
    { APPEARANCE,   "Appearance" },
    { INTELLIGENCE, "Intelligence" },
    { PERCEPTION,   "Perception" },
    { WITS,         "Wits" }
  };
}
