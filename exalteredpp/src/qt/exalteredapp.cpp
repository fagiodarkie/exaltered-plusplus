#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(QWidget *parent)
    : QWidget(parent)
{
  initLoadScreen();
  setWindowTitle(labels::APP_TITLE);
}

void ExalteredApp::initLoadScreen()
{
  loadCharacterScreen = new screen::QLoadCharacterScreen(this);
  QGridLayout *grid = new QGridLayout();
  grid->addWidget(loadCharacterScreen);
  setLayout(grid);
}

ExalteredApp::~ExalteredApp()
{

}
