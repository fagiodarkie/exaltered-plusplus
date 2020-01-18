#pragma once

#include <map>
#include <string>

#include "text/character_text_constants.h"
#include "common/reverse_search.h"

namespace attribute
{

  using namespace model::text::attribute_names;

  enum class attribute_enum
  {
    STRENGTH,     DEXTERITY,    CONSTITUTION,
    CHARISMA,     MANIPULATION, APPEARANCE,
    INTELLIGENCE, PERCEPTION,   WITS
  };

  enum attribute_category
  {
    SOCIAL, MENTAL, PHYSICAL
  };

  static const std::list<attribute_category> ATTRIBUTE_CATEGORIES = { PHYSICAL, SOCIAL, MENTAL};

  static const std::list<attribute_enum> ATTRIBUTES = {
    attribute_enum::STRENGTH,     attribute_enum::DEXTERITY,    attribute_enum::CONSTITUTION,
    attribute_enum::CHARISMA,     attribute_enum::MANIPULATION, attribute_enum::APPEARANCE,
    attribute_enum::INTELLIGENCE, attribute_enum::PERCEPTION,   attribute_enum::WITS
  };

  static const std::map<attribute_category, std::list<attribute_enum>> ATTRIBUTES_BY_CATEGORY
  { { SOCIAL,   { attribute_enum::CHARISMA,     attribute_enum::MANIPULATION, attribute_enum::APPEARANCE   } },
    { MENTAL,   { attribute_enum::INTELLIGENCE, attribute_enum::PERCEPTION,   attribute_enum::WITS         } },
    { PHYSICAL, { attribute_enum::STRENGTH,     attribute_enum::DEXTERITY,    attribute_enum::CONSTITUTION } }
  };

  static const std::map<attribute_category, std::string> ATTRIBUTE_CATEGORY_NAME
  { { SOCIAL,   ATTRIBUTE_CATEGORY_SOCIAL    },
    { PHYSICAL, ATTRIBUTE_CATEGORY_PHYSICAL  },
    { MENTAL,   ATTRIBUTE_CATEGORY_MENTAL    }
  };

  static const std::map<attribute_enum, std::string> ATTRIBUTE_NAME {
    { attribute_enum::STRENGTH,     ATTRIBUTE_STRENGTH      },
    { attribute_enum::DEXTERITY,    ATTRIBUTE_DEXTERITY     },
    { attribute_enum::CONSTITUTION, ATTRIBUTE_CONSTITUTION  },
    { attribute_enum::CHARISMA,     ATTRIBUTE_CHARISMA      },
    { attribute_enum::MANIPULATION, ATTRIBUTE_MANIPULATION  },
    { attribute_enum::APPEARANCE,   ATTRIBUTE_APPEARANCE    },
    { attribute_enum::INTELLIGENCE, ATTRIBUTE_INTELLIGENCE  },
    { attribute_enum::PERCEPTION,   ATTRIBUTE_PERCEPTION    },
    { attribute_enum::WITS,         ATTRIBUTE_WITS          }
  };

  static attribute_category ATTRIBUTE_CATEGORY_BY_NAME(const std::string& attribute_category_name)
  {
    return commons::reverse_search_in_map(ATTRIBUTE_CATEGORIES, ATTRIBUTE_CATEGORY_NAME, attribute_category_name);
  }

  static attribute_category CATEGORY_OF_ATTRIBUTE(attribute_enum att)
  {
    return *std::find_if(ATTRIBUTE_CATEGORIES.begin(), ATTRIBUTE_CATEGORIES.end(),
            [att](attribute_category category) -> bool {
        auto category_list = ATTRIBUTES_BY_CATEGORY.at(category);
        return std::find(category_list.begin(), category_list.end(), att) != category_list.end();
      });
  }
}
