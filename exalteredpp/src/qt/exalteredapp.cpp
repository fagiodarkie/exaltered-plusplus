#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(QWidget *parent)
    : QWidget(parent)
{
  init_load_character_screen();
  setWindowTitle(labels::APP_TITLE);
}

ExalteredApp::~ExalteredApp()
{

}
