#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(QSharedPointer<manager::character_manager> c_manager)
    : QMainWindow (), character_manager(c_manager)
{
  load_character_screen_widget = new qloadcharacterscreen(character_manager, this);
  init_load_character_screen();
  setWindowTitle(labels::APP_TITLE);
}

ExalteredApp::~ExalteredApp()
{

}
