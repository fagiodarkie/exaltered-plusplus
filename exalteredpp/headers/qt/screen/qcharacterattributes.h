#pragma once

#include <QWidget>
#include <QSharedPointer>
#include "character.h"

namespace qt {
  namespace screen {
    class qcharacterattributes : public QWidget
    {
    public:
      qcharacterattributes(std::shared_ptr<character::character> character, QWidget* parent);
    };
  }
}
