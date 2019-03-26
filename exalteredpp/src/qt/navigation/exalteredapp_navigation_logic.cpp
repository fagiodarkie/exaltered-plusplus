#include "exalteredapp.h"

#include <QGridLayout>
#include <QMenuBar>
#include <screen/qmainscreen.h>
#include <screen/qloadcharacterscreen.h>
#include <screen/qcharacterattributes.h>

using namespace qt::screen;

void ExalteredApp::load_character_screen()
{
  character_info_screen_widget = new qcharacterinfoscreen(current_character, character_manager, this);
  setCentralWidget(character_info_screen_widget);
}

void ExalteredApp::load_attributes_screen()
{
  character_attributes_widget = new qcharacterattributes(current_character, this);
  setCentralWidget(character_attributes_widget);
}

void ExalteredApp::load_main_screen(QSharedPointer<character::character> character)
{
  current_character = character;
  main_screen_widget = new qmainscreen(this);
  setCentralWidget(main_screen_widget);
  load_menu();
}

QLayout* ExalteredApp::create_layout_for_widget(QWidget *content) const
{
  QGridLayout *grid = new QGridLayout();
  grid->addWidget(content);
  return grid;
}

void ExalteredApp::load_menu()
{
  menuBar()->clear();

  QMenu *charMenu = menuBar()->addMenu("Character");

  QAction *load_character_screen = new QAction(charMenu);
  connect(load_character_screen, &QAction::triggered, this, &ExalteredApp::load_character_screen);
  load_character_screen->setText("Character Info");
  charMenu->addAction(load_character_screen);

  QAction *load_attributes_screen = new QAction(charMenu);
  connect(load_attributes_screen, &QAction::triggered, this, &ExalteredApp::load_attributes_screen);
  load_attributes_screen->setText("Character Attributes");
  charMenu->addAction(load_attributes_screen);
}

void ExalteredApp::init_load_character_screen()
{
  load_character_screen_widget = new qloadcharacterscreen(character_manager, this);
  setCentralWidget(load_character_screen_widget);

  connect(load_character_screen_widget, &qloadcharacterscreen::character_loaded, this, &ExalteredApp::load_main_screen);
}

void ExalteredApp::clear_layout(QWidget* current_layout)
{
  layout()->removeWidget(current_layout);
  delete layout();
  qDeleteAll(children());
}
