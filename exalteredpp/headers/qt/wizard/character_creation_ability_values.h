#pragma once

#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMap>

#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "exalt/exalt_caste.h"
#include "ability_value_row.h"
#include "widget/with_progress_bar.h"
#include "widget/with_next_continue_buttons.h"

namespace qt {
  namespace wizard {

    struct operation_enabled {
      bool increase, decrease, favorite, unfavorite;
    };

    struct validation_result
    {
      QMap<ability::ability_name, operation_enabled> operations;
      unsigned int total_spent, total_spent_in_favorites, remaining_favorites, remaining_caste_favorites;
    };

    class character_creation_ability_values : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT
    public:
      character_creation_ability_values(QWidget *parent = nullptr);

      void set_current_abilities(const ability::abilities& new_abilities,
                                 character::exalt::caste selected_caste,
                                 unsigned int number_of_caste_favorites,
                                 unsigned int number_of_free_favorites,
                                 unsigned int max_points,
                                 unsigned int min_in_favorites,
                                 unsigned int max_ability_value);

    signals:
      void abilities_chosen(ability::abilities& abilities);

    private:
      QMap<ability::ability_name, ability_value_row*> row_of_ability;
      void next_issued();
      validation_result check_current_selection();
      void regenerate_abilities();

      void on_ability_change();
      void on_new_declination();

      QWidget* abilities;
      QLabel *summary;
      ability::abilities _abilities;
      character::exalt::caste _caste;
      unsigned int caste_favorites, free_favorites, max_ability_points, min_points_in_favorites, max_std_ability_value;
    };
  }
}
