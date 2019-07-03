#pragma once

#include <QCheckBox>
#include <QPushButton>
#include <QWidget>

#include "abilities/abilities.h"
#include "abilities/ability_names.h"
#include "exalt/exalt_caste.h"

namespace qt {
  namespace wizard {
    class character_creation_ability_values : public QWidget
    {
      Q_OBJECT
    public:
      character_creation_ability_values(QWidget *parent = nullptr);
      void set_current_abilities(const character::abilities& new_abilities, character::exalt::caste selected_caste, unsigned int number_of_default_favorites, unsigned int number_of_favorite_abilities);

    signals:
      void back_issued();
      void abilities_selected(QList<character::ability_names::ability_enum> favorite_abilities);

    public slots:

    private:
      QMap<QCheckBox*, character::ability_names::ability_enum> ability_of_button;
      void next_issued();
      void check_current_selection();
      void allow_check_on_non_caste_abilities();

      QList<character::ability_names::ability_enum> selected_abilities() const;

      QPushButton *next_page, *cancel;
      character::abilities _abilities;
      unsigned int max_favorite;
      unsigned int default_favorite;
      QList<character::ability_names::ability_enum> abilities_of_caste;
    };
  }
}
