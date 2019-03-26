#include "exalteredapp.h"

#include "objects_factory.h"
#include <QGridLayout>
#include <screen/qmainscreen.h>
#include <screen/qloadcharacterscreen.h>

using namespace qt::screen;

void ExalteredApp::load_character_screen(QSharedPointer<character::character> character)
{
  character_screen_widget = new qmainscreen(character, qt::model_factory::s_character_manager, this);
  stacked_layout->addWidget(character_screen_widget);
  stacked_layout->setCurrentIndex(1);
}

QLayout* ExalteredApp::create_layout_for_widget(QWidget *content) const
{
  QGridLayout *grid = new QGridLayout();
  grid->addWidget(content);
  return grid;
}

void ExalteredApp::init_load_character_screen()
{
  load_character_screen_widget = new qloadcharacterscreen(qt::model_factory::s_character_manager, this);
  stacked_layout = new QStackedLayout();
  stacked_layout->addWidget(load_character_screen_widget);
  stacked_layout->setCurrentIndex(0);

  setLayout(stacked_layout);
  connect(load_character_screen_widget, &qloadcharacterscreen::character_loaded, this, &ExalteredApp::load_character_screen);
}

void ExalteredApp::clear_layout(QWidget* current_layout)
{
  layout()->removeWidget(current_layout);
  delete layout();
  qDeleteAll(children());
}
