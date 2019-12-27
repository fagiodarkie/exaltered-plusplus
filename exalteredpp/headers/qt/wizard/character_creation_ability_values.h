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
      void set_current_abilities(const character::abilities& new_abilities,
                                 character::exalt::caste selected_caste,
                                 unsigned int number_of_caste_favorites,
                                 unsigned int number_of_free_favorites,
                                 unsigned int max_points,
                                 unsigned int min_in_favorites,
                                 unsigned int max_ability_value);

    signals:
      void back_issued();
      void abilities_chosen(character::abilities& abilities);

    private:
      QMap<character::ability_names::ability_enum, ability_value_row*> row_of_ability;
      void next_issued();
      void check_current_selection();
      void regenerate_abilities();

      void ability_change(const character::ability_names::detailed_ability& detailed_ability, unsigned int new_value);

      QWidget* abilities;
      QPushButton *next_page, *cancel;
      character::abilities _abilities;
      character::exalt::caste _caste;
      unsigned int caste_favorites, free_favorites, max_ability_points, min_points_in_favorites, max_std_ability_value;
    };
  }
}
