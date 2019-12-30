#ifndef EXPERIENCE_DEFINES_H
#define EXPERIENCE_DEFINES_H

#include <map>
#include <string>

namespace character { namespace narrative {

    enum experience_expense_type {
      ATTRIBUTE, ABILITY, SPECIALISATION, CHARM, BACKGROUND, VIRTUE, VICE, WILLPOWER, ESSENCE,
      DUENDE, JABBERWOCKY_ART, EXULTANCY
    };

    static const std::map<experience_expense_type, std::string> EXPENSE_NAME = {
      { ATTRIBUTE,       "Attribute"        },
      { ABILITY,         "Ability"          },
      { SPECIALISATION,  "Specialisation"   },
      { CHARM,           "Charm"            },
      { BACKGROUND,      "Background"       },
      { VIRTUE,          "Virtue"           },
      { VICE,            "Vice"             },
      { WILLPOWER,       "Willpower"        },
      { ESSENCE,         "Essence"          },
      { DUENDE,          "Duende"           },
      { JABBERWOCKY_ART, "Jabberwocky Art"  },
      { EXULTANCY,       "Exultancy"        }
    };

} }
#endif // EXPERIENCE_DEFINES_H
