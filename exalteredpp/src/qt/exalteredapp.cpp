#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include "caste_style.h"
#include <QApplication>
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(manager::character_manager& c_manager,
                           calculator::derived_value_calculator& derived_values_calculator)
    : QMainWindow (), character_manager(c_manager), derived_values_calculator(derived_values_calculator)
{
  init_load_character_screen();
  setWindowTitle(labels::APP_TITLE);

  //setStyleSheet(qt::style::STYLE_OF(character::creation::TYPE_SOLAR_EXALT));
}

ExalteredApp::~ExalteredApp()
{

}
