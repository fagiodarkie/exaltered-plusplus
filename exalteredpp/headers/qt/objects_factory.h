#pragma once

#include <QSharedPointer>
#include "managers/character_manager.h"
#include "filesystem_db.h"
#include "abilities/abstract_ability_factory.h"
#include "abilities/default_ability_factory.h"

#define POINTER_TO(TYPE, VAR, ...) static const QSharedPointer<TYPE> VAR = QSharedPointer<TYPE>(__VA_ARGS__);

namespace qt
{
  namespace model_factory
  {
    using namespace serialisation;
    using namespace manager;
    using namespace character;

    POINTER_TO(db_abstraction,    s_db_abstraction,     new filesystem_db())
    POINTER_TO(abstract_ability_factory, s_ability_factory, new default_ability_factory())
    POINTER_TO(character_manager, s_character_manager,  new character_manager(s_db_abstraction, s_ability_factory))
  }
}
