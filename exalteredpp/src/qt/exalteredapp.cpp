#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(manager::character_manager& c_manager,
                           calculator::derived_value_calculator& derived_values_calculator)
    : QMainWindow (), character_manager(c_manager), derived_values_calculator(derived_values_calculator)
{
  init_load_character_screen();
  setWindowTitle(labels::APP_TITLE);

  setStyleSheet("QWidget { background-color: #15161c; color: #acaeb7; selection-background-color: #050607; }"
                "QGroupBox { border: 2px inset #aa7a49; padding: 4px; margin: 3px; } "
                "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 3px 0 3px; }"
                "QVBoxLayout { border: 1px inset #050607; } "
                "QScrollArea { border: 1px inset #050607; } "
                "QBorderLayout { border: 1px inset #050607; } "
                "QTabWidget::pane { border: 1px inset #050607; } "
                "QTabBar::tab { background-color: #15161c; border: 2px inset #050607; } "
                "QPushButton { background-color: #050607; color: #aa7a49; border: 2px inset #aa7a49; } "
                "QPushButton:disabled { background-color: #15161c; color: #acaeb7; }"
                "QSpinBox { border: 3 inset #050607; } "
                "QLabel { border-width: 0px; } "
                "QLineEdit { border: 1px inset #050607; background: #050607; } "
                "QPushButton:pressed { background-color: #acaeb7; }");
}

ExalteredApp::~ExalteredApp()
{

}
