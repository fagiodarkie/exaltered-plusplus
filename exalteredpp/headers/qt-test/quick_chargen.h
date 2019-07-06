#pragma once
#include "character.h"
#include <QSharedPointer>

QSharedPointer<character::character> generate_character_pointer(const QString& name, int id);

character::character generate_character(const QString& name, int id);
