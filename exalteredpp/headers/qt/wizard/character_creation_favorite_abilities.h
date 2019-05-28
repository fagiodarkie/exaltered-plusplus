#pragma once

#include <QPushButton>
#include <QWidget>

#include "abilities/ability_names.h"

namespace qt {
  namespace wizard {
    class character_creation_favorite_abilities : public QWidget
    {
      Q_OBJECT
    public:
      explicit character_creation_favorite_abilities(QWidget *parent = nullptr);

    signals:
      void back_issued();
      void abilities_selected(QList<character::ability_names::ability> favorite_abilities);

    public slots:

    private:
      QMap<QPushButton*, character::ability_names::ability> ability_of_button;
      void next_issued();
      void check_current_selection();

      QPushButton* generate_button(character::ability_names::ability ability);

      QPushButton *next_page, *cancel;
    };
  }
}

