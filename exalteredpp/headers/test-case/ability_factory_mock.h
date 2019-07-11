#pragma once

#include <QSharedPointer>
#include "abilities/abstract_ability_factory.h"

namespace mock_tests {

  class mock_ability_factory: public ::character::abstract_ability_factory
  {
  public:
    mock_ability_factory() : multiple_flag(false){ }

    void mock_incoming_multiple_ability(bool mock_it) { multiple_flag = mock_it; }

    ::character::ability_group get_ability_group(::character::ability_names::ability_enum ability) const
    {
      QList<::character::ability> ability_list_mult = { ::character::ability("ab_1", 1), ::character::ability("ab_2", 0) },
          single = { ::character::ability(::character::ability_names::ability_declination::NO_DECLINATION, 3) };
      ::character::ability_group result(::character::ability_names::ABILITY_NAME[ability], ::character::ability_names::CATEGORY_OF_ABILITY(ability),
                                      multiple_flag ? ability_list_mult : single);

      return result;
    }

  private:
    bool multiple_flag;
  };
}
