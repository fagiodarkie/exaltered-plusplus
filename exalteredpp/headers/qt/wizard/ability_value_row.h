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

using ability::ability_group;

namespace qt {
  namespace wizard {
    class ability_value_row : public QWidget
    {
      Q_OBJECT

    public:
      ability_value_row(const ability_group& model_ability_group);

      void add_rows(QFormLayout* form) const;

      ability_group ability() const;

      void update_operations(const std::string& declination, bool allow_increase, bool allow_decrease, bool allow_favorite, bool allow_unfavorite);

    private:

      ability_group _ability;

      void on_increase();
      void on_decrease();
      void on_fav_toggle();
      void show_declination_wizard() const;
      void add_new_declination(const QString& new_declination_name);

      QMap<std::string, QPushButton*> increase_ability_buttons, decrease_ability_buttons, make_favorite_buttons;
      QMap<std::string, widget::ability_declination_selector*> change_declination_buttons;
      QMap<std::string, QLabel*> ability_value_labels;
      QPushButton *add_declination;
      widget::add_ability_declination_dialog *declination_dialog;

      static const char* REFERRED_ABILITY;
      static const char* REFERRED_SUB_ABILITY;

    signals:
      void ability_change();
      void new_declination();
    };
  }
}

#endif // ABILITY_VALUE_ROW_H
