#pragma once

#include <QWidget>
#include <QSharedPointer>
#include "character.h"

namespace qt {
  namespace screen {
    class qcharacterabilities : public QWidget
    {
    public:
      qcharacterabilities(QSharedPointer<character::character> character, QWidget* parent);

    };
  }
}
