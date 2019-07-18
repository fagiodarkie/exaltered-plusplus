#pragma once

#include "managers/character_manager.h"
#include "filesystem_db.h"
#include "abilities/abstract_ability_factory.h"
#include "abilities/default_ability_factory.h"

#define POINTER_TO(TYPE, ACTUAL_TYPE, VAR, ...) std::shared_ptr<TYPE> VAR = std::make_shared<ACTUAL_TYPE>(__VA_ARGS__);
