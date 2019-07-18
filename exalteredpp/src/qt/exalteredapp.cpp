#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(manager::character_manager* const c_manager)
    : QMainWindow (), character_manager(c_manager)
{
  init_load_character_screen();
  setWindowTitle(labels::APP_TITLE);
}

ExalteredApp::~ExalteredApp()
{

}
