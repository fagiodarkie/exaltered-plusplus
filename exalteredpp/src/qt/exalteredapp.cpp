#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(QWidget *parent)
    : qt::main_screen_navigation_logic(parent, this)
{
  init_load_character_screen();
  setWindowTitle(labels::APP_TITLE);
}

ExalteredApp::~ExalteredApp()
{

}
