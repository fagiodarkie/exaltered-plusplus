#include "qt/exalteredapp.h"
#include <QApplication>

#include "caste_style.h"

#include "dependencies.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  qt::style::application(a);
  qt::style::SET_CASTE(character::creation::character_type::TYPE_SOLAR_EXALT);
  ExalteredApp w(dependency::s_character_manager, dependency::derived_values, dependency::s_equipment_manager);
  w.show();
  return a.exec();
}
