#ifndef ABILITY_VALUE_ROW_H
#define ABILITY_VALUE_ROW_H

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMap>

#include "widget/ability_declination_selector.h"

#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "exalt/exalt_caste.h"
#include "widget/add_ability_declination_dialog.h"

namespace qt {
  namespace wizard {
    class ability_value_row : public QWidget
    {
      Q_OBJECT

    public:
      ability_value_row(const ability::ability& model_ability);

      void add_row(QFormLayout* form) const;

      ability::ability ability() const;

      void update_operations(bool allow_increase, bool allow_decrease, bool allow_favorite, bool allow_unfavorite);

    signals:
      void ability_change();

    private:

      ability::ability _ability;

      void on_increase();
      void on_decrease();
      void on_fav_toggle();

      QPushButton* increase_ability_button, *decrease_ability_button, *make_favorite_button;
      QLabel* ability_value_label, *ability_name_label;
    };
  }
}

#endif // ABILITY_VALUE_ROW_H
