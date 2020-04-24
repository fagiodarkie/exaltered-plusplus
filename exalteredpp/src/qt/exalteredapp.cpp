#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include <QApplication>
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(std::shared_ptr<manager::character_manager>& c_manager,
                           std::shared_ptr<calculator::derived_value_calculator>& derived_values_calculator,
                           std::shared_ptr<manager::equipment_manager>& e_manager)
    : QMainWindow (), character_manager(c_manager), equip_manager(e_manager), derived_values_calculator(derived_values_calculator)
{
  init_load_character_screen();
  setWindowTitle(labels::APP_TITLE);
}

ExalteredApp::~ExalteredApp()
{

}
