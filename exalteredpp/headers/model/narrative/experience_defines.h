#ifndef EXPERIENCE_DEFINES_H
#define EXPERIENCE_DEFINES_H

#include <map>
#include <string>
#include <vector>

namespace narrative {

    enum experience_expense_type {
      ATTRIBUTE, ABILITY, SPECIALISATION, CHARM, BACKGROUND, VIRTUE, VICE, WILLPOWER, ESSENCE,
      DUENDE, JABBERWOCKY_ART, EXULTANCY
    };

    static const std::vector<experience_expense_type> EXPENSE_TYPES = {
      ATTRIBUTE, ABILITY, SPECIALISATION, CHARM, BACKGROUND, VIRTUE, VICE, WILLPOWER, ESSENCE,
      DUENDE, JABBERWOCKY_ART, EXULTANCY
    };

    enum experience_award_type {
      PLAYTIME,
      ROLEPLAY_CHARACTER,
      ROLEPLAY_TEAMMATES,
      ROLEPLAY_NARRATOR,
      MOTIVATION,
      NARRATION,
      LONG_TIME_CALIBRATION,
      STUNT,
      COOL,
      INTUITION,
      MEMENTO_AUDERE_SEMPER,
      ACTING_OSCAR,
      BOSSFIGHT,
      EASTER_EGG,
      VOLUNTEERING,
      DIVINE_GAME,
      COSPLAY
    };

    static const std::vector<experience_award_type> AWARD_TYPES = {
      PLAYTIME,
      ROLEPLAY_CHARACTER,
      ROLEPLAY_TEAMMATES,
      ROLEPLAY_NARRATOR,
      MOTIVATION,
      NARRATION,
      LONG_TIME_CALIBRATION,
      STUNT,
      COOL,
      INTUITION,
      MEMENTO_AUDERE_SEMPER,
      ACTING_OSCAR,
      BOSSFIGHT,
      EASTER_EGG,
      VOLUNTEERING,
      DIVINE_GAME,
      COSPLAY
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

    static const std::map<experience_award_type, std::string> AWARD_NAME = {
      { PLAYTIME,              "Playtime" },
      { ROLEPLAY_CHARACTER,    "Roleplay - Character immersion" },
      { ROLEPLAY_TEAMMATES,    "Roleplay - Teammates" },
      { ROLEPLAY_NARRATOR,     "Roleplay - Narrator" },
      { MOTIVATION,            "Motivation" },
      { NARRATION,             "Narrative goals" },
      { LONG_TIME_CALIBRATION, "Long time calibration" },
      { STUNT,                 "Stunt award" },
      { COOL,                  "Cool award" },
      { INTUITION,             "Intuition award" },
      { MEMENTO_AUDERE_SEMPER, "Memento Audere Semper" },
      { ACTING_OSCAR,          "Acting Oscar" },
      { BOSSFIGHT,             "Bossfight award" },
      { EASTER_EGG,            "Easter Egg award" },
      { VOLUNTEERING,          "Volunteering" },
      { DIVINE_GAME,           "Divine Game" },
      { COSPLAY,               "Cosplay award" }
    };

}
#endif // EXPERIENCE_DEFINES_H
