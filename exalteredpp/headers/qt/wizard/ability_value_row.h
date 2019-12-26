#ifndef ABILITY_VALUE_ROW_H
#define ABILITY_VALUE_ROW_H

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMap>

#include "abilities/abilities.h"
#include "abilities/ability_names.h"
#include "exalt/exalt_caste.h"

using character::ability_group;

namespace qt {
  namespace wizard {
    class ability_value_row : public QWidget
    {
      Q_OBJECT

    public:
      ability_value_row(const ability_group& model_ability_group);
      void update(const ability_group& new_ability_group);

      void add_rows(QFormLayout* form) const;

      ability_group ability() const;

    private:

      ability_group _ability;
      void update_labels();

      QMap<character::ability_names::detailed_ability, QPushButton*> increase_ability, decrease_ability;

      static const char* REFERRED_ABILITY;
      static const char* REFERRED_SUB_ABILITY;

    signals:
      void ability_change(const character::ability_names::detailed_ability& ability, unsigned int new_value);
    };
  }
}

#endif // ABILITY_VALUE_ROW_H
