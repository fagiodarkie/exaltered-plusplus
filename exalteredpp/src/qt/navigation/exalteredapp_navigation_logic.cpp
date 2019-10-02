#include "exalteredapp.h"

#include <QGridLayout>
#include <QMenuBar>
#include <QToolBar>
#include <screen/qmainscreen.h>
#include <screen/qloadcharacterscreen.h>
#include <screen/qcharacterattributes.h>

using namespace qt::screen;

QLayout* ExalteredApp::create_layout_for_widget(QWidget *content) const
{
  QGridLayout *grid = new QGridLayout();
  grid->addWidget(content);
  return grid;
}

void ExalteredApp::load_menu()
{
  QToolBar *charMenu = addToolBar("Character");

  QAction *load_character_screen = new QAction(charMenu);
  connect(load_character_screen, &QAction::triggered, this, &ExalteredApp::load_character_screen);
  load_character_screen->setText("Character Info");
  charMenu->addAction(load_character_screen);

  QAction *load_attributes_screen = new QAction(charMenu);
  connect(load_attributes_screen, &QAction::triggered, this, &ExalteredApp::load_attributes_screen);
  load_attributes_screen->setText("Character Attributes");
  charMenu->addAction(load_attributes_screen);

  QAction *load_abilities_screen = new QAction(charMenu);
  connect(load_abilities_screen, &QAction::triggered, this, &ExalteredApp::load_abilities_screen);
  load_abilities_screen->setText("Character Abilities");
  charMenu->addAction(load_abilities_screen);

  QAction *load_defenses_screen = new QAction(charMenu);
  connect(load_defenses_screen, &QAction::triggered, this, &ExalteredApp::load_vd_screen);
  load_defenses_screen->setText("Defense Values");
  charMenu->addAction(load_defenses_screen);

  QAction *load_essence_screen = new QAction(charMenu);
  connect(load_essence_screen, &QAction::triggered, this, &ExalteredApp::load_essence_screen);
  load_essence_screen->setText("Essence and Khan");
  charMenu->addAction(load_essence_screen);

  QAction *load_virtues_screen = new QAction(charMenu);
  connect(load_virtues_screen, &QAction::triggered, this, &ExalteredApp::load_virtues_screen);
  load_virtues_screen->setText("Willpower and Virtues");
  charMenu->addAction(load_virtues_screen);
}

void ExalteredApp::clear_layout(QWidget* current_layout)
{
  layout()->removeWidget(current_layout);
  delete layout();
  qDeleteAll(children());
}
