#pragma once

#include <QSharedPointer>
#include "managers/character_manager.h"
#include "filesystem_db.h"

#define POINTER_TO(TYPE, VAR, ...) static const QSharedPointer<TYPE> VAR = QSharedPointer<TYPE>(__VA_ARGS__);

namespace qt
{
  namespace model_factory
  {
    using namespace serialisation;
    using namespace manager;

    POINTER_TO(db_abstraction,    s_db_abstraction,     new filesystem_db())
    POINTER_TO(character_manager, s_character_manager,  new character_manager(s_db_abstraction))
  }
}
