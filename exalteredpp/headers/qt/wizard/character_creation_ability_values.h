#pragma once

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMap>

#include "abilities/abilities.h"
#include "abilities/ability_names.h"
#include "exalt/exalt_caste.h"
#include "ability_value_row.h"

namespace qt {
  namespace wizard {

    class character_creation_ability_values : public QWidget
    {
      Q_OBJECT
    public:
      character_creation_ability_values(QWidget *parent = nullptr);
      void set_current_abilities(const character::abilities& new_abilities, unsigned int max_points, unsigned int min_in_favorites, unsigned int max_ability_value);

    signals:
      void back_issued();
      void ability_points_chosen(const character::abilities& abilities);

    private:
      QMap<character::ability_names::ability_enum, ability_value_row> row_of_ability;
      void next_issued();
      void check_current_selection();

      void increase_issued();
      void decrease_issued();

      QPushButton *next_page, *cancel;
      character::abilities _abilities;
      unsigned int max_ability_points, min_points_in_favorites, max_std_ability_value;
    };
  }
}
