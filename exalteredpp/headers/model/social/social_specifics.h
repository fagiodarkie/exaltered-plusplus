#pragma once

#include <map>
#include "emotions_names.h"

namespace character {
  namespace social {

    enum specific {
      MOTIVATIONS,
      COMPULSIONS,
      ILLUSIONS,
      SERFDOMS,
      EMOTIONS
    };

    static const std::map<specific, std::string> SPECIFIC_NAMES = {
      { MOTIVATIONS, "Motivations" },
      { COMPULSIONS, "Compulsions" },
      { ILLUSIONS, "Illusions" },
      { SERFDOMS, "Serfdoms" },
      { EMOTIONS, "Emotions" }
    };

    static const std::map<virtues::virtue_enum, specific> SPECIFIC_UNDER_VIRTUE = {
      { virtues::COMPASSION, SERFDOMS },
      { virtues::CONVINCTION, MOTIVATIONS },
      { virtues::VALOR, COMPULSIONS },
      { virtues::TEMPERANCE, ILLUSIONS }
    };

    static const std::map<specific, std::map<social_degrees, std::string>> NAME_OF_SPECIFIC_GRADE =
    {
      { MOTIVATIONS, {
          { SUPERFICIAL, "Short-Term Motivations" },
          { RELEVANT, "Mid-Term Motivations" },
          { INTIMATE, "Long-Term Motivations" }
        } },
      { COMPULSIONS, {
          { SUPERFICIAL, "Logical Arguments" },
          { RELEVANT, "Compulsions" },
          { INTIMATE, "Total Control" }
        } },
      { ILLUSIONS, {
          { SUPERFICIAL, "Superficial Illusions" },
          { RELEVANT, "Judgmental Biases" },
          { INTIMATE, "Core Beliefs" }
        } },
      { SERFDOMS, {
          { SUPERFICIAL, "Acquaintances" },
          { RELEVANT, "Friends and Family" },
          { INTIMATE, "Close Friends and Partners" }
        } }
    };
  }
}
