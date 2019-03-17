#include "navigation/main_screen_navigation_logic.h"

#include <QGridLayout>

#include <screen/qmainscreen.h>
#include <screen/qloadcharacterscreen.h>

namespace qt {
  using namespace screen;

  main_screen_navigation_logic::main_screen_navigation_logic(QWidget *parent, QWidget* screen)
    : QWidget (parent)
  {
    master_screen = QPointer<QWidget>(screen);
  }

  void main_screen_navigation_logic::load_character_screen(QSharedPointer<character::character> character) const
  {
    qmainscreen* character_screen = new qmainscreen(character, master_screen);
    master_screen->setLayout(create_layout_for_widget(character_screen));
    master_screen->repaint();
  }

  QLayout* main_screen_navigation_logic::create_layout_for_widget(QWidget *content) const
  {
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(content);
    return grid;
  }

  void main_screen_navigation_logic::init_load_character_screen()
  {
    qloadcharacterscreen* load_character_screen = new qloadcharacterscreen(master_screen);
    connect(load_character_screen, &qloadcharacterscreen::character_loaded, this, &main_screen_navigation_logic::load_character_screen);
  }
}
