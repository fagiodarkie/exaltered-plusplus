#include "screen/qmainscreen.h"

#include <layout/qborderlayout.h>

namespace qt
{
  using namespace layout;

  namespace screen
  {
    qmainscreen::qmainscreen(QSharedPointer<character::character> character, QWidget *parent)
      : QWidget(parent), character(character), character_name_widget(character->getName())
    {
      QBorderLayout* outerLayout = new QBorderLayout();
      outerLayout->addWidget(&character_name_widget, QBorderLayout::North);
      setLayout(outerLayout);
    }
  }
}
