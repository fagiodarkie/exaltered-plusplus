#pragma once

#include <QWidget>
#include "character.h"
#include "derived_value_calculator.h"

namespace qt {
  namespace screen {
    class qessence_values_screen : public QWidget
    {
      Q_OBJECT
    public:
      qessence_values_screen(const std::shared_ptr<character::character> c, QWidget *parent = nullptr);
    };
  }
}
