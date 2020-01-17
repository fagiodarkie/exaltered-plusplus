#include "qt-test/quick_chargen.h"

std::shared_ptr<character::character> generate_character_pointer(const QString& name, int id)
{
  return std::make_shared<character::character>(name.toStdString(), character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, attribute::attributes(), ability::abilities(), virtues::virtues(), power::essence(), power::willpower(), power::health(), power::logos(), id);
}

character::character generate_character(const QString& name, int id)
{
  return character::character(name.toStdString(), character::creation::TYPE_MORTAL_HERO, character::exalt::caste::NO_CASTE, attribute::attributes(), ability::abilities(), virtues::virtues(), power::essence(), power::willpower(), power::health(), power::logos(), id);
}

