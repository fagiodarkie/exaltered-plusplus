#pragma once

#include <QComboBox>
#include <QWidget>
#include "character.h"
#include "derived_value_calculator.h"

namespace qt {
  namespace screen {
    class qdefense_values_screen : public QWidget
    {
      Q_OBJECT
    public:
      qdefense_values_screen(const std::shared_ptr<character::character> c, const calculator::derived_value_calculator& derived_values, QWidget *parent = nullptr);

    private:
      void update_values();

      const std::shared_ptr<character::character> _character;
      const calculator::derived_value_calculator& _calculator;

      QComboBox *physical_parry_ability;
    };
  }
}
