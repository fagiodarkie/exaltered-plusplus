#ifndef IMPROVEMENT_H
#define IMPROVEMENT_H

#include <map>
#include <vector>
#include <string>

namespace equipment {
  namespace craft {
    enum class improvement_enum
    {
      PRECISION,
      DEFENSE,
      REDUCE_MINIMUM_ATTRIBUTE,
      REDUCE_ENCUMBRANCE,
      RANGE_10PC,
      AGGRAVATED_SOAK,
      LETHAL_SOAK,
      BASHING_SOAK_2PTS,
      LETHAL_DAMAGE,
      BASHING_DAMAGE_2PTS,
      DRILL,
      MIN_DAMAGE
    };

    static std::vector<improvement_enum> IMPROVEMENTS =
    {
      improvement_enum::PRECISION,
      improvement_enum::DEFENSE,
      improvement_enum::REDUCE_MINIMUM_ATTRIBUTE,
      improvement_enum::REDUCE_ENCUMBRANCE,
      improvement_enum::RANGE_10PC,
      improvement_enum::AGGRAVATED_SOAK,
      improvement_enum::LETHAL_SOAK,
      improvement_enum::BASHING_SOAK_2PTS,
      improvement_enum::LETHAL_DAMAGE,
      improvement_enum::BASHING_DAMAGE_2PTS,
      improvement_enum::DRILL,
      improvement_enum::MIN_DAMAGE
    };

    static std::map<improvement_enum, std::string> IMPROVEMENT_NAME = {
      { improvement_enum::PRECISION,                "Increase Precision (1 point)"},
      { improvement_enum::DEFENSE,                  "Increase Defense (1 point)"},
      { improvement_enum::REDUCE_MINIMUM_ATTRIBUTE, "Reduce Minimum Attribute (1 point)"},
      { improvement_enum::REDUCE_ENCUMBRANCE,       "Reduce Armor Encumbrance (1 point)"},
      { improvement_enum::RANGE_10PC,               "Increase Range  (10 %)"},
      { improvement_enum::AGGRAVATED_SOAK,          "Increase Aggravated Soak (1 point)"},
      { improvement_enum::LETHAL_SOAK,              "Increase Lethal Soak (1 point)"},
      { improvement_enum::BASHING_SOAK_2PTS,        "Increase Bashing Soak (2 points)"},
      { improvement_enum::LETHAL_DAMAGE,            "Increase Lethal Damage (1 point)"},
      { improvement_enum::BASHING_DAMAGE_2PTS,      "Increase Bashing Damage (2 points)"},
      { improvement_enum::DRILL,                    "Increase Drill (1 point)"},
      { improvement_enum::MIN_DAMAGE,               "Increase Minimum Damage (1 point)"}
    };

    static std::map<improvement_enum, unsigned short int> IMPROVEMENT_MAKE_SIZE = {
      { improvement_enum::PRECISION,                1},
      { improvement_enum::DEFENSE,                  2},
      { improvement_enum::REDUCE_MINIMUM_ATTRIBUTE, 3},
      { improvement_enum::REDUCE_ENCUMBRANCE,       3},
      { improvement_enum::RANGE_10PC,               1},
      { improvement_enum::AGGRAVATED_SOAK,          2},
      { improvement_enum::LETHAL_SOAK,              1},
      { improvement_enum::BASHING_SOAK_2PTS,        1},
      { improvement_enum::LETHAL_DAMAGE,            1},
      { improvement_enum::BASHING_DAMAGE_2PTS,      1},
      { improvement_enum::DRILL,                    2},
      { improvement_enum::MIN_DAMAGE,               2}
    };


} }
#endif // IMPROVEMENT_H
