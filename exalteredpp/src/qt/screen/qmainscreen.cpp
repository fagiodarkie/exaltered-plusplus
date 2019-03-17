#include "screen/qmainscreen.h"

#include <QVBoxLayout>

namespace qt
{
  namespace screen
  {
    qmainscreen::qmainscreen(QSharedPointer<character::character> character, QWidget *parent) : QWidget(parent), character(character)
    {

    }
  }
}
