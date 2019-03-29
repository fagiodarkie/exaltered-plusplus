#pragma once


#include <QSharedPointer>
#include "abilities/abstract_ability_factory.h"

namespace character_manager_tests {

  class mock_db_abstraction: public character::abstract_ability_factory
  {


    // abstract_ability_factory interface
  public:

    void mock_incoming_multiple_ability(bool mock_it) { multiple_flag = mock_it; }

    character::ability_group get_ability_group(character::ability_name ability) const
    {
      character::ability_group result(character::ABILITY_NAME[ability], )
    }

  private:
    bool multiple_flag;
  };
}
