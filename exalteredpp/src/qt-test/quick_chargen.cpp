#include "qt-test/quick_chargen.h"

QSharedPointer<character::character> generate_character_pointer(const QString& name, int id)
{
  return QSharedPointer<character::character>(new character::character(name, character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, character::attributes(), character::abilities(), character::virtues::virtues(), character::power::power_container(), id));
}

character::character generate_character(const QString& name, int id)
{
  return character::character(name, character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, character::attributes(), character::abilities(), character::virtues::virtues(), character::power::power_container(), id);
}

