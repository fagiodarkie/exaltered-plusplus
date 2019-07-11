#pragma once

#include <QMap>
#include <QString>

#include "text/character_text_constants.h"
#include "common/reverse_search.h"

namespace character
{
  namespace attribute_names {

    using namespace model::text::character::attribute_names;

    enum attribute
    {
      STRENGTH, DEXTERITY, CONSTITUTION,
      CHARISMA, MANIPULATION, APPEARANCE,
      INTELLIGENCE, PERCEPTION, WITS
    };

    enum attribute_category
    {
      SOCIAL, MENTAL, PHYSICAL
    };

    static const QList<attribute_category> ATTRIBUTE_CATEGORIES = {SOCIAL, MENTAL, PHYSICAL};

    static const QList<attribute> ATTRIBUTES = {
      STRENGTH, DEXTERITY, CONSTITUTION,
      CHARISMA, MANIPULATION, APPEARANCE,
      INTELLIGENCE, PERCEPTION, WITS
    };

    static const QMap<attribute_category, QList<attribute>> ATTRIBUTES_BY_CATEGORY
    { { SOCIAL, {CHARISMA, MANIPULATION, APPEARANCE } },
      { MENTAL, {INTELLIGENCE, PERCEPTION, WITS } },
      { PHYSICAL, {STRENGTH, DEXTERITY, CONSTITUTION } }
    };

    static const QMap<attribute_category, QString> ATTRIBUTE_CATEGORY_NAME
    { { SOCIAL,   ATTRIBUTE_CATEGORY_SOCIAL    },
      { PHYSICAL, ATTRIBUTE_CATEGORY_PHYSICAL  },
      { MENTAL,   ATTRIBUTE_CATEGORY_MENTAL    }
    };

    static const QMap<attribute, QString> ATTRIBUTE_NAME {
      { STRENGTH,     ATTRIBUTE_STRENGTH      },
      { DEXTERITY,    ATTRIBUTE_DEXTERITY     },
      { CONSTITUTION, ATTRIBUTE_CONSTITUTION  },
      { CHARISMA,     ATTRIBUTE_CHARISMA      },
      { MANIPULATION, ATTRIBUTE_MANIPULATION  },
      { APPEARANCE,   ATTRIBUTE_APPEARANCE    },
      { INTELLIGENCE, ATTRIBUTE_INTELLIGENCE  },
      { PERCEPTION,   ATTRIBUTE_PERCEPTION    },
      { WITS,         ATTRIBUTE_WITS          }
    };

    static attribute_category ATTRIBUTE_CATEGORY_BY_NAME(const QString& attribute_category_name)
    {
      return commons::reverse_search_in_map(ATTRIBUTE_CATEGORIES, ATTRIBUTE_CATEGORY_NAME, attribute_category_name);
    }

    static attribute_category CATEGORY_OF_ATTRIBUTE(attribute att)
    {
      return *std::find_if(ATTRIBUTE_CATEGORIES.begin(), ATTRIBUTE_CATEGORIES.end(),
              [att](attribute_category category) -> bool { return ATTRIBUTES_BY_CATEGORY[category].contains(att); });
    }
  }
}
