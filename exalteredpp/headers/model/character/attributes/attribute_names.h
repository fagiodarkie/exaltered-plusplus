#pragma once

#include <QMap>
#include <QString>

namespace character
{
  namespace attribute_names {
    enum attribute_name
    {
      STRENGTH, DEXTERITY, CONSTITUTION,
      CHARISMA, MANIPULATION, APPEARANCE,
      INTELLIGENCE, PERCEPTION, WITS
    };

    enum attribute_category
    {
      SOCIAL, MENTAL, PHYSICAL
    };

    static const QMap<attribute_category, QList<attribute_name>> ATTRIBUTES_BY_CATEGORY
    { { SOCIAL, {CHARISMA, MANIPULATION, APPEARANCE } },
      { MENTAL, {INTELLIGENCE, PERCEPTION, WITS } },
      { PHYSICAL, {STRENGTH, DEXTERITY, CONSTITUTION } }
    };

    static const QMap<attribute_category, QString> ATTRIBUTE_CATEGORY_NAME
    { { SOCIAL,   "Social" },
      { PHYSICAL, "Physical" },
      { MENTAL,   "Mental" }
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
}
