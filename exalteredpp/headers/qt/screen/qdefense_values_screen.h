#pragma once

#include <QComboBox>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "character.h"
#include "derived_value_calculator.h"

namespace qt {
  namespace screen {
    class qdefense_values_screen : public QWidget
    {
      Q_OBJECT
    public:
      qdefense_values_screen(const std::shared_ptr<character::character> c, const calculator::derived_value_calculator& derived_values, QWidget *parent = nullptr);

    signals:
      void attack_wizard_invoked();
      void defense_wizard_invoked();

    private:
      void update_values();

      const std::shared_ptr<character::character> _character;
      const calculator::derived_value_calculator& _calculator;

      QComboBox *physical_parry_ability;
      QPushButton *attack_wizard, *defense_wizard;

      QLabel *dodge_dv,
             *parry_dv,
             *heavy_parry_dv,
             *parry_balance,
             *dodge_balance,

             *mental_dodge_dv,
             *charisma_pdv,
             *manipulation_pdv,
             *appearance_pdv,

             *natural_soak;
    };
  }
}
