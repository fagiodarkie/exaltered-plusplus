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

  {
    QAction *load_character_screen = new QAction(charMenu);
    connect(load_character_screen, &QAction::triggered, this, &ExalteredApp::load_character_screen);
    load_character_screen->setText("Character Info");
    charMenu->addAction(load_character_screen);
  }

  {
    QAction *load_attributes_screen = new QAction(charMenu);
    connect(load_attributes_screen, &QAction::triggered, this, &ExalteredApp::load_attributes_screen);
    load_attributes_screen->setText("Character Attributes");
    charMenu->addAction(load_attributes_screen);
  }

  {
    QAction *load_abilities_screen = new QAction(charMenu);
    connect(load_abilities_screen, &QAction::triggered, this, &ExalteredApp::load_abilities_screen);
    load_abilities_screen->setText("Character Abilities");
    charMenu->addAction(load_abilities_screen);
  }
}


void ExalteredApp::clear_layout(QWidget* current_layout)
{
  layout()->removeWidget(current_layout);
  delete layout();
  qDeleteAll(children());
}
