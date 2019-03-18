#include "exalteredapp.h"

#include <QGridLayout>

#include <screen/qmainscreen.h>
#include <screen/qloadcharacterscreen.h>

using namespace qt::screen;

void ExalteredApp::load_character_screen(QSharedPointer<character::character> character)
{
  clear_layout(load_character_screen_widget);
  character_screen_widget = new qmainscreen(character, this);
  setLayout(create_layout_for_widget(character_screen_widget));
}

QLayout* ExalteredApp::create_layout_for_widget(QWidget *content) const
{
  QGridLayout *grid = new QGridLayout();
  grid->addWidget(content);
  return grid;
}

void ExalteredApp::init_load_character_screen()
{
  load_character_screen_widget = new qloadcharacterscreen(this);
  setLayout(create_layout_for_widget(load_character_screen_widget));
  connect(load_character_screen_widget, &qloadcharacterscreen::character_loaded, this, &ExalteredApp::load_character_screen);
}

void ExalteredApp::clear_layout(QWidget* current_layout)
{
  layout()->removeWidget(current_layout);
  delete layout();
  qDeleteAll(children());
}
